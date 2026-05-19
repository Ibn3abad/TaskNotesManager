/**
 * @author     A. KHOUK
 * @date       12.09.2024
 * @version    0.8
 * @copyright  Copyright (c) 2026, A. KHOUK.
 * @license    MIT licence
 */

#include "TodoModel.h"

#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QUuid>

TodoModel::TodoModel(DatabaseManager *databaseManager, QObject *parent)
    : QAbstractListModel(parent),
      m_databaseManager(databaseManager)
{
}

int TodoModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return m_todos.count();
}

QVariant TodoModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= m_todos.count()) {
        return {};
    }

    const TodoItem &todo = m_todos.at(index.row());
    switch (role) {
    case IdRole: return todo.id;
    case TaskIdRole: return todo.taskId;
    case TextRole: return todo.text;
    case DoneRole: return todo.done;
    case CreatedAtRole: return todo.createdAt;
    case UpdatedAtRole: return todo.updatedAt;
    default: return {};
    }
}

bool TodoModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || index.row() < 0 || index.row() >= m_todos.count()) {
        return false;
    }

    if (role == DoneRole) {
        return toggleTodo(m_todos.at(index.row()).id, value.toBool());
    }

    return false;
}

Qt::ItemFlags TodoModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) {
        return Qt::NoItemFlags;
    }

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;
}

QHash<int, QByteArray> TodoModel::roleNames() const
{
    return {
        {IdRole, "todoId"},
        {TaskIdRole, "taskId"},
        {TextRole, "text"},
        {DoneRole, "done"},
        {CreatedAtRole, "createdAt"},
        {UpdatedAtRole, "updatedAt"}
    };
}

QString TodoModel::currentTaskId() const
{
    return m_currentTaskId;
}

int TodoModel::openCount() const
{
    int count = 0;
    for (const TodoItem &todo : m_todos) {
        if (!todo.done) {
            ++count;
        }
    }
    return count;
}

int TodoModel::doneCount() const
{
    int count = 0;
    for (const TodoItem &todo : m_todos) {
        if (todo.done) {
            ++count;
        }
    }
    return count;
}

void TodoModel::loadForTask(const QString &taskId)
{
    beginResetModel();
    m_todos.clear();
    m_currentTaskId = taskId;

    if (!taskId.isEmpty()) {
        QSqlQuery query(m_databaseManager->database());
        query.prepare(QStringLiteral(
            "SELECT id, task_id, text, done, created_at, updated_at FROM todos "
            "WHERE task_id = :taskId ORDER BY done ASC, created_at ASC"));
        query.bindValue(QStringLiteral(":taskId"), taskId);

        if (!query.exec()) {
            qWarning() << "Load todos failed:" << query.lastError().text();
        } else {
            while (query.next()) {
                TodoItem todo;
                todo.id = query.value(0).toString();
                todo.taskId = query.value(1).toString();
                todo.text = query.value(2).toString();
                todo.done = query.value(3).toInt() == 1;
                todo.createdAt = query.value(4).toString();
                todo.updatedAt = query.value(5).toString();
                m_todos.append(todo);
            }
        }
    }

    endResetModel();
    emit currentTaskChanged();
    emit todoListChanged();
}

bool TodoModel::addTodo(const QString &taskId, const QString &text)
{
    const QString cleanText = text.trimmed();
    if (taskId.isEmpty() || cleanText.isEmpty()) {
        return false;
    }

    const QString id = QUuid::createUuid().toString(QUuid::WithoutBraces);
    QSqlQuery query(m_databaseManager->database());
    query.prepare(QStringLiteral(
        "INSERT INTO todos (id, task_id, text, done) "
        "VALUES (:id, :taskId, :text, 0)"));
    query.bindValue(QStringLiteral(":id"), id);
    query.bindValue(QStringLiteral(":taskId"), taskId);
    query.bindValue(QStringLiteral(":text"), cleanText);

    if (!query.exec()) {
        qWarning() << "Insert todo failed:" << query.lastError().text();
        return false;
    }

    loadForTask(taskId);
    return true;
}

bool TodoModel::toggleTodo(const QString &id, bool done)
{
    if (id.isEmpty()) {
        return false;
    }

    QSqlQuery query(m_databaseManager->database());
    query.prepare(QStringLiteral(
        "UPDATE todos SET done = :done, updated_at = CURRENT_TIMESTAMP WHERE id = :id"));
    query.bindValue(QStringLiteral(":id"), id);
    query.bindValue(QStringLiteral(":done"), done ? 1 : 0);

    if (!query.exec()) {
        qWarning() << "Toggle todo failed:" << query.lastError().text();
        return false;
    }

    const int idx = indexOfTodo(id);
    if (idx >= 0) {
        m_todos[idx].done = done;
        emit dataChanged(index(idx), index(idx), {DoneRole});
        emit todoListChanged();
    } else {
        loadForTask(m_currentTaskId);
    }

    return true;
}

bool TodoModel::deleteTodo(const QString &id)
{
    if (id.isEmpty()) {
        return false;
    }

    QSqlQuery query(m_databaseManager->database());
    query.prepare(QStringLiteral("DELETE FROM todos WHERE id = :id"));
    query.bindValue(QStringLiteral(":id"), id);

    if (!query.exec()) {
        qWarning() << "Delete todo failed:" << query.lastError().text();
        return false;
    }

    loadForTask(m_currentTaskId);
    return true;
}

int TodoModel::indexOfTodo(const QString &id) const
{
    if (id.isEmpty()) {
        return -1;
    }

    for (int i = 0; i < m_todos.count(); ++i) {
        if (m_todos.at(i).id == id) {
            return i;
        }
    }
    return -1;
}

/**
 * @author     A. KHOUK
 * @date       12.09.2024
 * @version    0.9
 * @copyright  Copyright (c) 2026, A. KHOUK.
 * @license    MIT licence
 */

#include "TaskModel.h"

#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QUuid>

TaskModel::TaskModel(DatabaseManager *databaseManager, QObject *parent)
    : QAbstractListModel(parent),
      m_databaseManager(databaseManager)
{
    reload();
}

int TaskModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return m_tasks.count();
}

QVariant TaskModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= m_tasks.count()) {
        return {};
    }

    const TaskItem &task = m_tasks.at(index.row());
    switch (role) {
    case IdRole: return task.id;
    case TitleRole: return task.title;
    case DescriptionRole: return task.description;
    case StatusRole: return task.status;
    case PriorityRole: return task.priority;
    case DueDateRole: return task.dueDate;
    case CreatedAtRole: return task.createdAt;
    case SelectedRole: return task.id == m_selectedTaskId;
    default: return {};
    }
}

QHash<int, QByteArray> TaskModel::roleNames() const
{
    return {
        {IdRole, "taskId"},
        {TitleRole, "title"},
        {DescriptionRole, "description"},
        {StatusRole, "status"},
        {PriorityRole, "priority"},
        {DueDateRole, "dueDate"},
        {CreatedAtRole, "createdAt"},
        {SelectedRole, "selected"}
    };
}

QString TaskModel::selectedTaskId() const
{
    return m_selectedTaskId;
}

QString TaskModel::selectedTaskTitle() const
{
    const int idx = indexOfTask(m_selectedTaskId);
    return idx >= 0 ? m_tasks.at(idx).title : QString();
}

QString TaskModel::selectedTaskDescription() const
{
    const int idx = indexOfTask(m_selectedTaskId);
    return idx >= 0 ? m_tasks.at(idx).description : QString();
}

QString TaskModel::selectedTaskStatus() const
{
    const int idx = indexOfTask(m_selectedTaskId);
    return idx >= 0 ? m_tasks.at(idx).status : QString();
}

QString TaskModel::selectedTaskPriority() const
{
    const int idx = indexOfTask(m_selectedTaskId);
    return idx >= 0 ? m_tasks.at(idx).priority : QStringLiteral("medium");
}

QString TaskModel::filterMode() const
{
    return m_filterMode;
}

void TaskModel::reload()
{
    beginResetModel();
    m_tasks.clear();

    QSqlQuery query(m_databaseManager->database());

    QString sql = QStringLiteral(
        "SELECT id, title, description, status, priority, due_date, created_at "
        "FROM tasks");

    if (m_filterMode == QStringLiteral("open")) {
        sql += QStringLiteral(" WHERE status = 'open'");
    } else if (m_filterMode == QStringLiteral("in_progress")) {
        sql += QStringLiteral(" WHERE status = 'in_progress'");
    } else if (m_filterMode == QStringLiteral("done")) {
        sql += QStringLiteral(" WHERE status = 'done'");
    } else if (m_filterMode == QStringLiteral("high")) {
        sql += QStringLiteral(" WHERE priority = 'high'");
    }

    sql += QStringLiteral(" ORDER BY created_at DESC");
    query.prepare(sql);

    if (!query.exec()) {
        qWarning() << "Load tasks failed:" << query.lastError().text();
    } else {
        while (query.next()) {
            TaskItem task;
            task.id = query.value(0).toString();
            task.title = query.value(1).toString();
            task.description = query.value(2).toString();
            task.status = query.value(3).toString();
            task.priority = query.value(4).toString();
            task.dueDate = query.value(5).toString();
            task.createdAt = query.value(6).toString();
            m_tasks.append(task);
        }
    }

    endResetModel();

    if (!m_selectedTaskId.isEmpty() && indexOfTask(m_selectedTaskId) < 0) {
        m_selectedTaskId.clear();
        emit selectedTaskChanged();
    }

    emit taskListChanged();
}

bool TaskModel::addTask(const QString &title, const QString &description, const QString &priority)
{
    const QString cleanTitle = title.trimmed();
    if (cleanTitle.isEmpty()) {
        return false;
    }

    const QString id = QUuid::createUuid().toString(QUuid::WithoutBraces);

    QSqlQuery query(m_databaseManager->database());
    query.prepare(QStringLiteral(
        "INSERT INTO tasks (id, title, description, status, priority) "
        "VALUES (:id, :title, :description, 'open', :priority)"));
    query.bindValue(QStringLiteral(":id"), id);
    query.bindValue(QStringLiteral(":title"), cleanTitle);
    query.bindValue(QStringLiteral(":description"), description.trimmed());
    query.bindValue(QStringLiteral(":priority"), priority.isEmpty() ? QStringLiteral("medium") : priority);

    if (!query.exec()) {
        qWarning() << "Insert task failed:" << query.lastError().text();
        return false;
    }

    reload();
    selectTask(id);
    return true;
}

bool TaskModel::deleteTask(const QString &id)
{
    if (id.isEmpty()) {
        return false;
    }

    QSqlQuery query(m_databaseManager->database());
    query.prepare(QStringLiteral("DELETE FROM tasks WHERE id = :id"));
    query.bindValue(QStringLiteral(":id"), id);

    if (!query.exec()) {
        qWarning() << "Delete task failed:" << query.lastError().text();
        return false;
    }

    const bool wasSelected = (id == m_selectedTaskId);
    reload();
    if (wasSelected) {
        clearSelection();
    }
    return true;
}

bool TaskModel::updateTask(const QString &id, const QString &title, const QString &description, const QString &status, const QString &priority)
{
    if (id.isEmpty() || title.trimmed().isEmpty()) {
        return false;
    }

    QSqlQuery query(m_databaseManager->database());
    query.prepare(QStringLiteral(
        "UPDATE tasks SET title = :title, description = :description, status = :status, "
        "priority = :priority, updated_at = CURRENT_TIMESTAMP WHERE id = :id"));
    query.bindValue(QStringLiteral(":id"), id);
    query.bindValue(QStringLiteral(":title"), title.trimmed());
    query.bindValue(QStringLiteral(":description"), description.trimmed());
    query.bindValue(QStringLiteral(":status"), status.isEmpty() ? QStringLiteral("open") : status);
    query.bindValue(QStringLiteral(":priority"), priority.isEmpty() ? QStringLiteral("medium") : priority);

    if (!query.exec()) {
        qWarning() << "Update task failed:" << query.lastError().text();
        return false;
    }

    reload();
    selectTask(id);
    return true;
}

void TaskModel::selectTask(const QString &id)
{
    if (!id.isEmpty() && indexOfTask(id) < 0) {
        clearSelection();
        return;
    }

    if (m_selectedTaskId == id) {
        return;
    }

    const QString oldId = m_selectedTaskId;
    m_selectedTaskId = id;
    emitSelectionDataChanged(oldId, m_selectedTaskId);
    emit selectedTaskChanged();
}

void TaskModel::clearSelection()
{
    selectTask(QString());
}

void TaskModel::setFilterMode(const QString &filterMode)
{
    QString normalized = filterMode.toLower();
    if (normalized.isEmpty()) {
        normalized = QStringLiteral("all");
    }

    if (normalized != QStringLiteral("all") &&
        normalized != QStringLiteral("open") &&
        normalized != QStringLiteral("in_progress") &&
        normalized != QStringLiteral("done") &&
        normalized != QStringLiteral("high")) {
        normalized = QStringLiteral("all");
    }

    if (m_filterMode == normalized) {
        return;
    }

    m_filterMode = normalized;
    reload();
    emit filterChanged();
}

int TaskModel::indexOfTask(const QString &id) const
{
    if (id.isEmpty()) {
        return -1;
    }

    for (int i = 0; i < m_tasks.count(); ++i) {
        if (m_tasks.at(i).id == id) {
            return i;
        }
    }
    return -1;
}

void TaskModel::emitSelectionDataChanged(const QString &oldId, const QString &newId)
{
    const int oldIndex = indexOfTask(oldId);
    if (oldIndex >= 0) {
        emit dataChanged(index(oldIndex), index(oldIndex), {SelectedRole});
    }

    const int newIndex = indexOfTask(newId);
    if (newIndex >= 0) {
        emit dataChanged(index(newIndex), index(newIndex), {SelectedRole});
    }
}

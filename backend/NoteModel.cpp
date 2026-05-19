/**
 * @author     A. KHOUK
 * @date       12.09.2024
 * @version    0.8
 * @copyright  Copyright (c) 2026, A. KHOUK.
 * @license    MIT licence
 */

#include "NoteModel.h"

#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QUuid>

NoteModel::NoteModel(DatabaseManager *databaseManager, QObject *parent)
    : QAbstractListModel(parent),
      m_databaseManager(databaseManager)
{
}

int NoteModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return m_notes.count();
}

QVariant NoteModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= m_notes.count()) {
        return {};
    }

    const NoteItem &note = m_notes.at(index.row());
    switch (role) {
    case IdRole: return note.id;
    case TaskIdRole: return note.taskId;
    case TitleRole: return note.title;
    case ContentRole: return note.content;
    case UpdatedAtRole: return note.updatedAt;
    default: return {};
    }
}

QHash<int, QByteArray> NoteModel::roleNames() const
{
    return {
        {IdRole, "noteId"},
        {TaskIdRole, "taskId"},
        {TitleRole, "title"},
        {ContentRole, "content"},
        {UpdatedAtRole, "updatedAt"}
    };
}

QString NoteModel::currentTaskId() const
{
    return m_currentTaskId;
}

void NoteModel::loadForTask(const QString &taskId)
{
    beginResetModel();
    m_notes.clear();
    m_currentTaskId = taskId;

    if (!taskId.isEmpty()) {
        QSqlQuery query(m_databaseManager->database());
        query.prepare(QStringLiteral(
            "SELECT id, task_id, title, content, updated_at FROM notes "
            "WHERE task_id = :taskId ORDER BY updated_at DESC"));
        query.bindValue(QStringLiteral(":taskId"), taskId);

        if (!query.exec()) {
            qWarning() << "Load notes failed:" << query.lastError().text();
        } else {
            while (query.next()) {
                NoteItem note;
                note.id = query.value(0).toString();
                note.taskId = query.value(1).toString();
                note.title = query.value(2).toString();
                note.content = query.value(3).toString();
                note.updatedAt = query.value(4).toString();
                m_notes.append(note);
            }
        }
    }

    endResetModel();
    emit currentTaskChanged();
}

bool NoteModel::addNote(const QString &taskId, const QString &title, const QString &content)
{
    if (taskId.isEmpty() || (title.trimmed().isEmpty() && content.trimmed().isEmpty())) {
        return false;
    }

    const QString id = QUuid::createUuid().toString(QUuid::WithoutBraces);
    QSqlQuery query(m_databaseManager->database());
    query.prepare(QStringLiteral(
        "INSERT INTO notes (id, task_id, title, content) "
        "VALUES (:id, :taskId, :title, :content)"));
    query.bindValue(QStringLiteral(":id"), id);
    query.bindValue(QStringLiteral(":taskId"), taskId);
    query.bindValue(QStringLiteral(":title"), title.trimmed().isEmpty() ? QStringLiteral("Neue Notiz") : title.trimmed());
    query.bindValue(QStringLiteral(":content"), content.trimmed());

    if (!query.exec()) {
        qWarning() << "Insert note failed:" << query.lastError().text();
        return false;
    }

    loadForTask(taskId);
    return true;
}

bool NoteModel::deleteNote(const QString &id)
{
    if (id.isEmpty()) {
        return false;
    }

    QSqlQuery query(m_databaseManager->database());
    query.prepare(QStringLiteral("DELETE FROM notes WHERE id = :id"));
    query.bindValue(QStringLiteral(":id"), id);

    if (!query.exec()) {
        qWarning() << "Delete note failed:" << query.lastError().text();
        return false;
    }

    loadForTask(m_currentTaskId);
    return true;
}

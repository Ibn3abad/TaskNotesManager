/**
 * @author     A. KHOUK
 * @date       12.09.2024
 * @version    0.9
 * @copyright  Copyright (c) 2026, A. KHOUK.
 * @license    MIT licence
 */

#ifndef NOTEMODEL_H
#define NOTEMODEL_H

#include <QAbstractListModel>
#include <QVector>

#include "DatabaseManager.h"

struct NoteItem
{
    QString id;
    QString taskId;
    QString title;
    QString content;
    QString updatedAt;
};

class NoteModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QString currentTaskId READ currentTaskId NOTIFY currentTaskChanged)

public:
    enum Roles {
        IdRole = Qt::UserRole + 1,
        TaskIdRole,
        TitleRole,
        ContentRole,
        UpdatedAtRole
    };
    Q_ENUM(Roles)

    explicit NoteModel(DatabaseManager *databaseManager, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    QString currentTaskId() const;

    Q_INVOKABLE void loadForTask(const QString &taskId);
    Q_INVOKABLE bool addNote(const QString &taskId, const QString &title, const QString &content);
    Q_INVOKABLE bool deleteNote(const QString &id);

signals:
    void currentTaskChanged();

private:
    DatabaseManager *m_databaseManager;
    QVector<NoteItem> m_notes;
    QString m_currentTaskId;
};

#endif // NOTEMODEL_H

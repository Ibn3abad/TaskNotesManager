/**
 * @author     A. KHOUK
 * @date       12.09.2024
 * @version    0.8
 * @copyright  Copyright (c) 2026, A. KHOUK.
 * @license    MIT licence
 */

#ifndef TODOMODEL_H
#define TODOMODEL_H

#include <QAbstractListModel>
#include <QVector>

#include "DatabaseManager.h"

struct TodoItem
{
    QString id;
    QString taskId;
    QString text;
    bool done = false;
    QString createdAt;
    QString updatedAt;
};

class TodoModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QString currentTaskId READ currentTaskId NOTIFY currentTaskChanged)
    Q_PROPERTY(int openCount READ openCount NOTIFY todoListChanged)
    Q_PROPERTY(int doneCount READ doneCount NOTIFY todoListChanged)

public:
    enum Roles {
        IdRole = Qt::UserRole + 1,
        TaskIdRole,
        TextRole,
        DoneRole,
        CreatedAtRole,
        UpdatedAtRole
    };
    Q_ENUM(Roles)

    explicit TodoModel(DatabaseManager *databaseManager, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QHash<int, QByteArray> roleNames() const override;

    QString currentTaskId() const;
    int openCount() const;
    int doneCount() const;

    Q_INVOKABLE void loadForTask(const QString &taskId);
    Q_INVOKABLE bool addTodo(const QString &taskId, const QString &text);
    Q_INVOKABLE bool toggleTodo(const QString &id, bool done);
    Q_INVOKABLE bool deleteTodo(const QString &id);

signals:
    void currentTaskChanged();
    void todoListChanged();

private:
    int indexOfTodo(const QString &id) const;

    DatabaseManager *m_databaseManager;
    QVector<TodoItem> m_todos;
    QString m_currentTaskId;
};

#endif // TODOMODEL_H

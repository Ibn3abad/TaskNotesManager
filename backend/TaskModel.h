/**
 * @author     A. KHOUK
 * @date       12.09.2024
 * @version    0.9
 * @copyright  Copyright (c) 2026, A. KHOUK.
 * @license    MIT licence
 */

#ifndef TASKMODEL_H
#define TASKMODEL_H

#include <QAbstractListModel>
#include <QVector>

#include "DatabaseManager.h"

struct TaskItem
{
    QString id;
    QString title;
    QString description;
    QString status;
    QString priority;
    QString dueDate;
    QString createdAt;
};

class TaskModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QString selectedTaskId READ selectedTaskId NOTIFY selectedTaskChanged)
    Q_PROPERTY(QString selectedTaskTitle READ selectedTaskTitle NOTIFY selectedTaskChanged)
    Q_PROPERTY(QString selectedTaskDescription READ selectedTaskDescription NOTIFY selectedTaskChanged)
    Q_PROPERTY(QString selectedTaskStatus READ selectedTaskStatus NOTIFY selectedTaskChanged)
    Q_PROPERTY(QString selectedTaskPriority READ selectedTaskPriority NOTIFY selectedTaskChanged)
    Q_PROPERTY(QString filterMode READ filterMode NOTIFY filterChanged)

public:
    enum Roles {
        IdRole = Qt::UserRole + 1,
        TitleRole,
        DescriptionRole,
        StatusRole,
        PriorityRole,
        DueDateRole,
        CreatedAtRole,
        SelectedRole
    };
    Q_ENUM(Roles)

    explicit TaskModel(DatabaseManager *databaseManager, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    QString selectedTaskId() const;
    QString selectedTaskTitle() const;
    QString selectedTaskDescription() const;
    QString selectedTaskStatus() const;
    QString selectedTaskPriority() const;
    QString filterMode() const;

    Q_INVOKABLE void reload();
    Q_INVOKABLE bool addTask(const QString &title, const QString &description = QString(), const QString &priority = QStringLiteral("medium"));
    Q_INVOKABLE bool deleteTask(const QString &id);
    Q_INVOKABLE bool updateTask(const QString &id, const QString &title, const QString &description, const QString &status, const QString &priority);
    Q_INVOKABLE void selectTask(const QString &id);
    Q_INVOKABLE void clearSelection();
    Q_INVOKABLE void setFilterMode(const QString &filterMode);

signals:
    void selectedTaskChanged();
    void taskListChanged();
    void filterChanged();

private:
    int indexOfTask(const QString &id) const;
    void emitSelectionDataChanged(const QString &oldId, const QString &newId);

    DatabaseManager *m_databaseManager;
    QVector<TaskItem> m_tasks;
    QString m_selectedTaskId;
    QString m_filterMode = QStringLiteral("all");
};

#endif // TASKMODEL_H

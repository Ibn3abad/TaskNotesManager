/**
 * @author     A. KHOUK
 * @date       12.09.2024
 * @version    0.9
 * @copyright  Copyright (c) 2026, A. KHOUK.
 * @license    MIT licence
 */

#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QString>

class DatabaseManager : public QObject
{
    Q_OBJECT

public:
    explicit DatabaseManager(QObject *parent = nullptr);
    ~DatabaseManager() override;

    bool openDatabase();
    QSqlDatabase database() const;

    Q_INVOKABLE QString databasePath() const;

private:
    bool createTables();
    QString buildDatabasePath() const;

    QSqlDatabase m_database;
    QString m_connectionName;
    QString m_databasePath;
};

#endif // DATABASEMANAGER_H

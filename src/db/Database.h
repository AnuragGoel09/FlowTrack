#pragma once
#include <QString>
#include <QSqlDatabase>

class Database {
public:
    explicit Database(const QString& path);
    ~Database();
    
    void migrateIfNeeded();

    static void initDefault(); // open/create DB and tables
    static QSqlDatabase defaultConnection();

    bool insertCommit(const QString& hash, const QString& branch, const QString& message, const QString& author, const QString& timestamp);
    bool commitExists(const QString& hash);
private:
    QSqlDatabase _db;
    QString _path;
};

#include "Database.h"
#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QStandardPaths>
#include <QDebug>
#include <QDir>
#include <QFile>

QString DB_FILENAME = "flowTrack-db";

Database::Database(const QString &path): _path(path)
{
    if (!QDir().exists(QFileInfo(path).absolutePath())) {
        QDir().mkpath(QFileInfo(path).absolutePath());
    }

    _db = QSqlDatabase::addDatabase("QSQLITE", "flowTrack_connection");
    _db.setDatabaseName(path);
    if (!_db.open()) {
        qFatal("Cannot open SQLite DB: %s", qPrintable(_db.lastError().text()));
    }
}

Database::~Database() {
    if (_db.isOpen()) _db.close();
    QSqlDatabase::removeDatabase("flowTrack_connection");
}

bool Database::initDefault() {
    
    QString dbDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(dbDir);

    if (!dir.exists()) {
        dir.mkpath(".");  // <-- Create full path first
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    QString dbPath = dbDir + "/flowTrack.db";

    db.setDatabaseName(dbPath);

    if (!db.open()) {
        qDebug() << "DB Open error:" << db.lastError().text();
        return false;
    }

    QSqlQuery query;

    // Create repositories table
    QString createRepoTable = R"(
        CREATE TABLE IF NOT EXISTS repositories (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            repoName TEXT NOT NULL,
            repoPath TEXT NOT NULL UNIQUE,
            createdOn DATETIME DEFAULT CURRENT_TIMESTAMP
        )
    )";

    if (!query.exec(createRepoTable)) {
        qDebug() << "Repo Table Error:" << query.lastError().text();
        return false;
    }

    // Create offline queue table
    QString createQueueTable = R"(
        CREATE TABLE IF NOT EXISTS eventQueue (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            jsonData TEXT NOT NULL,
            createdOn DATETIME DEFAULT CURRENT_TIMESTAMP,
            status TEXT DEFAULT 'queued'
        )
    )";

    if (!query.exec(createQueueTable)) {
        qDebug() << "Queue Table Error:" << query.lastError().text();
        return false;
    }

    return true;
}

QSqlDatabase Database::defaultConnection() {
    return QSqlDatabase::database("flowtrack_connection");
}

void Database::migrateIfNeeded() {
    // migrations.sql should create commits table
    QSqlQuery q(_db);
    bool ok = q.exec(R"(
        CREATE TABLE IF NOT EXISTS commits (
          commitHash TEXT PRIMARY KEY,
          branch TEXT,
          message TEXT,
          author TEXT,
          timestamp TEXT,
          processedAt TEXT
        );
    )");
    if (!ok) qDebug() << "Migration failed:" << q.lastError().text();
}

bool Database::insertCommit(const QString &hash, const QString &branch, const QString &message, const QString &author, const QString &timestamp) {
    if (commitExists(hash)) return false;
    QSqlQuery q(_db);
    q.prepare("INSERT INTO commits(commitHash, branch, message, author, timestamp, processedAt) VALUES (?, ?, ?, ?, ?, datetime('now'))");
    q.addBindValue(hash);
    q.addBindValue(branch);
    q.addBindValue(message);
    q.addBindValue(author);
    q.addBindValue(timestamp);
    if (!q.exec()) {
        qDebug() << "Insert failed:" << q.lastError().text();
        return false;
    }
    return true;
}

bool Database::commitExists(const QString &hash) {
    QSqlQuery q(_db);
    q.prepare("SELECT COUNT(1) FROM commits WHERE commitHash = ?");
    q.addBindValue(hash);
    if (!q.exec()) return false;
    if (q.next()) {
        return q.value(0).toInt() > 0;
    }
    return false;
}

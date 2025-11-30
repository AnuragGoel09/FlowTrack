#pragma once
#include <QObject>
#include <QString>

class Database;
class GitEvent;

class EventProcessor : public QObject {
    Q_OBJECT
public:
    explicit EventProcessor(Database* db, QObject* parent = nullptr);
    void processEventJson(const QString& jsonText);
    void processQueuedEvents(); // reads queue dir and processes
    void stop();
private:
    Database* _db;
    QString queuePath() const;
};

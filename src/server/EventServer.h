#pragma once
#include <QTcpServer>
#include <QObject>

class Database;
class EventProcessor;

class EventServer : public QTcpServer {
    Q_OBJECT
public:
    EventServer(Database* db, EventProcessor* processor, QObject* parent = nullptr);
    void start(quint16 port);
    void stop();

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private:
    Database* _db;
    EventProcessor* _processor;
};

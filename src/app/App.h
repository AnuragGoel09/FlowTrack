#pragma once
#include <QObject>
#include <memory>
#include "../db/Database.h"        // <-- include full Database
#include "../server/EventServer.h" // <-- include full EventServer
#include "../processor/EventProcessor.h" // <-- include full EventProcessor

class Database;
class EventServer;
class EventProcessor;

class App : public QObject {
    Q_OBJECT
public:
    static App* instance();
    void start();
    void stop();

    Database* database() const;
    EventServer* server() const;
    EventProcessor* processor() const;

private:
    explicit App(QObject* parent = nullptr);
    static App* _inst;

    std::unique_ptr<Database> _db;
    std::unique_ptr<EventServer> _server;
    std::unique_ptr<EventProcessor> _processor;
};

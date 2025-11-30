#include "EventServer.h"
#include "../db/Database.h"
#include "../processor/EventProcessor.h"
#include <QTcpSocket>
#include <QJsonDocument>
#include <QDebug>

EventServer::EventServer(Database* db, EventProcessor* processor, QObject* parent)
    : QTcpServer(parent), _db(db), _processor(processor) {}

void EventServer::start(quint16 port) {
    if (!this->listen(QHostAddress::LocalHost, port)) {
        qDebug() << "Failed to start EventServer on port" << port;
    } else {
        qDebug() << "EventServer listening on" << port;
    }
}

void EventServer::stop() {
    this->close();
}

void EventServer::incomingConnection(qintptr socketDescriptor) {
    QTcpSocket* socket = new QTcpSocket();
    if (!socket->setSocketDescriptor(socketDescriptor)) {
        delete socket;
        return;
    }

    connect(socket, &QTcpSocket::readyRead, [this, socket]() {
        QByteArray all = socket->readAll();
        // Very minimal HTTP POST parser: find header and Content-Length
        QString s = QString::fromUtf8(all);
        int pos = s.indexOf("\r\n\r\n");
        if (pos == -1) {
            socket->disconnectFromHost();
            return;
        }
        QString header = s.left(pos);
        QString body = s.mid(pos + 4);
        // parse Content-Length if present and ensure full body read (basic)
        int contentLength = 0;
        for (auto line : header.split("\r\n")) {
            if (line.startsWith("Content-Length:", Qt::CaseInsensitive)) {
                contentLength = line.split(":").last().trimmed().toInt();
            }
        }
        // If body length less than contentLength, wait (simplified: assume full arrives)
        Q_UNUSED(contentLength);
        // Very basic routing: handle POST /event
        if (header.startsWith("POST /event")) {
            // process JSON body
            _processor->processEventJson(body);
            // respond 200
            QByteArray resp = "HTTP/1.1 200 OK\r\nContent-Length: 2\r\n\r\nOK";
            socket->write(resp);
        } else {
            QByteArray resp = "HTTP/1.1 404 Not Found\r\nContent-Length: 9\r\n\r\nNotFound";
            socket->write(resp);
        }
        socket->flush();
        socket->disconnectFromHost();
    });

    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
}

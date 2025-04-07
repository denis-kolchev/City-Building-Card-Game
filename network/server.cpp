#include "server.h"
#include "jsons/jsongameinit.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QTcpSocket>
#include <QTimer>

Server::Server(int playerCount, QObject *parent)
    : m_playerCount(playerCount)
    , QObject(parent)
    , tcpServer(new QTcpServer(this)) {}

bool Server::startListening(quint16 port)
{
    if (!tcpServer->listen(QHostAddress::Any, port)) {
        emit logMessage("Server error: " + tcpServer->errorString());
        return false;
    }

    connect(tcpServer, &QTcpServer::newConnection, this, &Server::newConnection);
    return true;
}

QString Server::errorString()
{
    return tcpServer->errorString();
}

void Server::newConnection()
{
    while (tcpServer->hasPendingConnections()) {
        QTcpSocket *socket = tcpServer->nextPendingConnection();
        clients << socket;

        // Assign unique ID
        int assignedId = nextClientId++;
        clientIds[socket] = assignedId;

        connect(socket, &QTcpSocket::readyRead, this, &Server::readData);
        connect(socket, &QTcpSocket::disconnected, this, &Server::clientDisconnected);

        emit logMessage(QString("New client connected with ID: %1").arg(assignedId));

        // Send the ID to the client
        QJsonObject idMessage;
        idMessage["type"] = "assign_id";
        idMessage["player_id"] = assignedId;
        socket->write(QJsonDocument(idMessage).toJson());
        socket->waitForBytesWritten();

        // if server is listened by needed amount of pleayers
        if (clientIds.size() == m_playerCount) {
            QTimer::singleShot(100, this, [this]() {  // 100ms delay
                JsonGameInit gameInit(m_playerCount);
                QJsonObject gameInitMessage = gameInit.json();
                emit logMessage(QString("Server broadcasts: %1").arg(gameInit.type()));
                broadcast(gameInitMessage);
            });

            // JsonGameInit gameInit(m_playerCount);
            // QJsonObject gameInitMessage = gameInit.json();
            // emit logMessage(QString("Server broadcasts: %1").arg(gameInit.type()));
            // broadcast(gameInitMessage);
        }
    }
}

void Server::readData()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    QJsonDocument doc = QJsonDocument::fromJson(socket->readAll());

    if (!doc.isNull()) {
        emit newMessage(doc.object());
        broadcast(doc.object());
    }
}

void Server::broadcast(const QJsonObject &message)
{
    QByteArray data = QJsonDocument(message).toJson();
    for (QTcpSocket *client : std::as_const(clients)) {
        if (client->state() == QTcpSocket::ConnectedState) {
            client->write(data);
            client->waitForBytesWritten();
        }
    }
}

void Server::clientDisconnected()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    clients.removeAll(socket);
    socket->deleteLater();
    emit logMessage("Client disconnected");
}

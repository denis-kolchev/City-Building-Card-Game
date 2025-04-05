#include "server.h"
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>

Server::Server(QObject *parent) : QObject(parent), tcpServer(new QTcpServer(this)) {}

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
    for (QTcpSocket *client : clients) {
        if (client->state() == QTcpSocket::ConnectedState) {
            client->write(data);
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

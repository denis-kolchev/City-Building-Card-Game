#include "client.h"
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>

Client::Client(QObject *parent) : QObject(parent), socket(new QTcpSocket(this))
{
    connect(socket, &QTcpSocket::readyRead, this, &Client::readyRead);
    connect(socket, &QTcpSocket::disconnected, this, &Client::socketDisconnected);
}

void Client::connectToServer(const QHostAddress &host, quint16 port)
{
    socket->connectToHost(host, port);
    emit logMessage("Connecting to " + host.toString() + ":" + QString::number(port));
}

void Client::send(const QJsonObject &message)
{
    if (socket->state() == QTcpSocket::ConnectedState) {
        socket->write(QJsonDocument(message).toJson());
    }
}

void Client::readyRead()
{
    QJsonDocument doc = QJsonDocument::fromJson(socket->readAll());
    if (!doc.isNull()) {
        QJsonObject obj = doc.object();

        if (obj["type"] == "assign_id") {
            int id = obj["player_id"].toInt();
            emit logMessage(QString("Assigned player ID: %1").arg(id));
            // Store the ID locally if needed
        } else {
            emit newMessage(obj);
        }
    }
}

void Client::socketDisconnected()
{
    emit logMessage("Disconnected from server");
    emit disconnected();
}

bool Client::isConnected() const
{
    return socket->state() == QTcpSocket::ConnectedState;
}

#include "client.h"
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

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

/* Handles all jsons sent from UI (or even from GameLogic I didn't get it by far)
 * In the future this function should be replaced by strategy pattern to shorten it */

/*
 * Standardized JSON message format:
 * {
 *  "type": "message_type"
 *  "timestamp": "ISO8601_timestamp"
 * }
 */

void Client::readyRead()
{
    qDebug() << "is reade to read";
    QJsonDocument doc = QJsonDocument::fromJson(socket->readAll());
    if (doc.isNull()) {
        QByteArray data = socket->readAll();
        qDebug() << "Raw data:" << data;
        qDebug() << "Data length:" << data.length();

        qDebug() << "doc is null";
        return;
    }

    qDebug() << "json doc is not null";

    QJsonObject obj = doc.object();

    if (obj["type"] == "assign_id") {
        qDebug() << "------ type == assign_id";
        int id = obj["player_id"].toInt();
        emit logMessage(QString("Assigned player ID: %1").arg(id));
        // Store the ID locally if needed
    } else if (obj["type"] == "game_init") {
        qDebug() << "------ type == game_init";
        auto jsonData = obj["data"].toObject();
        int playerCount = jsonData["player_count"].toInt();
        emit networkGameInit(playerCount);
        emit logMessage(QString("networkGameInit: playerCount: %1").arg(playerCount));
    } else if (obj["type"] == "dice_roll_result") {
        qDebug() << "------ type == dice_roll_result";
        auto jsonData = obj["data"].toObject();
        int playerId = jsonData["player_id"].toInt();
        auto array = jsonData["results"].toArray();
        QVector<int> rollResult;
        for (const QJsonValue& value : array) {
            if (value.isDouble()) { // JSON numbers are always double
                rollResult.append(value.toInt());
            }
        }
        qDebug() << tr("Client: networkDiceRollResult << %1 << %2 << %3")
                   .arg(playerId)
                   .arg(rollResult[0])
                   .arg(rollResult[1]);

        emit networkDiceRollResult(playerId, rollResult);
    } else {
        emit newMessage(obj);
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

void Client::disconnectFromHost()
{
    socket->disconnectFromHost();
}

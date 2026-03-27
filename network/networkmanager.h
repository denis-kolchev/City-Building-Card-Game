#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include "client.h"
#include "jsonmessagefactory.h"
#include "jsons/abstractjsonstrategy.h"
#include "server.h"

#include <QHostAddress>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class NetworkManager : public QObject
{
    Q_OBJECT

public:
    NetworkManager(QObject *parent = nullptr);

    ~NetworkManager();

signals:
    void notifyPlayerWithMessageBox(QString message);

    // outside signals:
    void networkFinishIncomeState(int playerCount);
    void networkGameInit(int playerCount);
    void networkDiceRollResult(int playerId, QVector<int> rollResult);

public slots:
    void createClient(const QString &host, quint16 port);

    void createServer(const QString &host, quint16 port, int playerCount);

    void broadcastDiceRollResult(int playerId, QVector<int> rolls);

    void broadcastFinishIncomeState(int playerId);

    void sendMessage(const QString& message);

    void sendMessage(const AbstractJsonPtr& message);

private slots:
    void handleNewMessage(const QJsonObject &message);

    void onNewConnection();

    void onSocketDisconnected();

    void onSocketReadyRead();

private:
    QJsonObject createMessage(const QString &text);

    void logMessage(const QString &message);

    void setupClient(const QString &connectedMessage);

private:
    Server *m_server = nullptr;
    Client *m_client = nullptr;
    JsonMessageFactory *m_jsonFactory;
    bool m_isHost;

};

#endif // NETWORKMANAGER_H

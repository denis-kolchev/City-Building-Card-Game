#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

//#include "client.h"
//#include "server.h"

#include <QHostAddress>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class NetworkManager : public QObject
{
    Q_OBJECT

public:
    NetworkManager(QObject *parent = nullptr);

    void extracted();
    ~NetworkManager();

public slots:
    void connectPlayer(int playerId, QHostAddress &host, quint16 port);

    void messageReceived(QString message);

private slots:
    void onNewConnection();

    void onSocketDisconnected();

    void onSocketReadyRead();

private:
    void createClient(int playerId, QHostAddress &host, quint16 port);

    void createServer(int playerId, QHostAddress &host, quint16 port);

    void logMessage(const QString &message);

private:
    // Network
    QTcpServer *m_server;
    QList<QTcpSocket*> m_clientList;
    QTcpSocket *m_clientSocket;
    QList<int> m_playerIds;

    bool m_isHost;
};

#endif // NETWORKMANAGER_H

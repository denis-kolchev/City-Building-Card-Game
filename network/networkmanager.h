#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include "client.h"
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

public slots:
    void createClient(const QString &host, quint16 port);

    void createServer(const QString &host, quint16 port);

    void messageReceived(QString message);

private slots:
    void handleNewMessage(const QJsonObject &message);

    void onNewConnection();

    void onSocketDisconnected();

    void onSocketReadyRead();

private:
    QJsonObject createMessage(const QString &text);

    void logMessage(const QString &message);

    void sendMessage(const QString& message);

private:
    Server *m_server;
    Client *m_client;
    bool m_isHost;

};

#endif // NETWORKMANAGER_H

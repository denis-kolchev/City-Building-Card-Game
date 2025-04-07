#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QJsonDocument>

class Client : public QObject
{
    Q_OBJECT

public:
    explicit Client(QObject *parent = nullptr);
    void connectToServer(const QHostAddress &host, quint16 port);
    void send(const QJsonObject &message);
    bool isConnected() const;
    void disconnectFromHost();

signals:
    void newMessage(const QJsonObject &message);
    void logMessage(const QString &message);
    void connected();
    void disconnected();

    // outside signals:
    void networkGameInit(int playerCount);
    void networkDiceRollResult(int playerId, QVector<int> rollResult);

private slots:
    void readyRead();
    void socketDisconnected();

private:
    QTcpSocket *socket;
};

#endif // CLIENT_H

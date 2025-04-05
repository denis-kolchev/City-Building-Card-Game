#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QJsonDocument>

class Server : public QObject
{
    Q_OBJECT

public:
    explicit Server(QObject *parent = nullptr);
    QString errorString();
    bool startListening(quint16 port);
    void stop();
    void broadcast(const QJsonObject &message);


signals:
    void newMessage(const QJsonObject &message);
    void logMessage(const QString &message);

private slots:
    void newConnection();
    void readData();
    void clientDisconnected();

private:
    QTcpServer *tcpServer;
    QList<QTcpSocket*> clients;
    QMap<QTcpSocket*, int> clientIds;
    int nextClientId = 1;
};

#endif // SERVER_H

#include "networkmanager.h"

#include <QDateTime>
#include <QMessageBox>

NetworkManager::NetworkManager(QObject *parent)
{

}

NetworkManager::~NetworkManager()
{
    if (m_server) {
        m_server->close();
        delete m_server;
    }

    for (auto socket : std::as_const(m_clientList)) {
        socket->close();
        socket->deleteLater();
    }

    if (m_clientSocket) {
        m_clientSocket->close();
        m_clientSocket->deleteLater();
    }
}

void NetworkManager::connectPlayer(int playerId,
                                   QHostAddress &host,
                                   quint16 port)
{
    if (m_server) {
        createClient(playerId, host, port);
        return;
    }

    createServer(playerId, host, port);

}

void NetworkManager::messageReceived(QString message)
{
    if (message.isEmpty()) {
        return;
    }

    QByteArray data = message.toUtf8();

    if (m_isHost) {
        // Broadcast to all clients
        for (QTcpSocket *client : std::as_const(m_clientList)) {
            client->write(data);
        }
        logMessage(QString("You (host): %1").arg(message));
    } else {
        if (m_clientSocket && m_clientSocket->state() == QAbstractSocket::ConnectedState) {
            m_clientSocket->write(data);
            logMessage(QString("You: %1").arg(message));
        } else {
            logMessage("Not connected to server!");
        }
    }
}

void NetworkManager::onNewConnection()
{
    while (m_server->hasPendingConnections()) {
        QTcpSocket *socket = m_server->nextPendingConnection();
        m_clientList.append(socket);

        connect(socket, &QTcpSocket::readyRead, this, &NetworkManager::onSocketReadyRead);
        connect(socket, &QTcpSocket::disconnected, this, &NetworkManager::onSocketDisconnected);

        logMessage(QString("New client connected: %1:%2")
                       .arg(socket->peerAddress().toString())
                       .arg(socket->peerPort()));
    }
}

void NetworkManager::onSocketDisconnected()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if (!socket) return;

    if (m_isHost) {
        m_clientList.removeOne(socket);
        logMessage(QString("Client disconnected: %1:%2")
                       .arg(socket->peerAddress().toString())
                       .arg(socket->peerPort()));
    } else {
        logMessage("Disconnected from server");
        m_clientSocket->deleteLater();
        m_clientSocket = nullptr;
    }

    socket->deleteLater();
}

void NetworkManager::onSocketReadyRead()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if (!socket) return;

    QByteArray data = socket->readAll();
    QString message = QString::fromUtf8(data);

    if (m_isHost) {
        // Broadcast to all clients except the sender
        for (QTcpSocket *client : std::as_const(m_clientList)) {
            if (client != socket) {
                client->write(data);
            }
        }
        logMessage(QString("Client %1:%2: %3")
                       .arg(socket->peerAddress().toString())
                       .arg(socket->peerPort())
                       .arg(message));
    } else {
        logMessage(QString("Server: %1").arg(message));
    }
}

void NetworkManager::createClient(int playerId,
                                  QHostAddress &host,
                                  quint16 port)
{
    if (m_clientSocket) {
        logMessage("Already connected to a server!");
        return;
    }

    if (host.isNull()) {
        logMessage("Invalid Host, please enter a valid host address");
        return;
    }

    m_clientSocket = new QTcpSocket(this);
    connect(m_clientSocket, &QTcpSocket::connected, this, [this]() {
        logMessage("Connected to server!");
    });
    connect(m_clientSocket, &QTcpSocket::readyRead, this, &NetworkManager::onSocketReadyRead);
    connect(m_clientSocket, &QTcpSocket::disconnected, this, &NetworkManager::onSocketDisconnected);
    connect(m_clientSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::errorOccurred),
            this, [this](QAbstractSocket::SocketError error) {
                logMessage("Socket error: " + m_clientSocket->errorString());
            });

    m_clientSocket->connectToHost(host, port);
    m_isHost = false;
    logMessage(QString("Connecting to %1:%2...").arg(host.toString(), QString::number(port)));
}

void NetworkManager::createServer(int playerId,
                                  QHostAddress &host,
                                  quint16 port)
{
    m_server = new QTcpServer(this);
    if (!m_server->listen(QHostAddress::Any, port)) {
        logMessage("Failed to start server: " + m_server->errorString());
        delete m_server;
        m_server = nullptr;
        return;
    }

    connect(m_server, &QTcpServer::newConnection, this, &NetworkManager::onNewConnection);

    m_isHost = true;
    logMessage(QString("Server started on port %1. Waiting for connections...").arg(port));
}

void NetworkManager::logMessage(const QString &message)
{
    qDebug() << QString("[%1] %2")
                    .arg(QDateTime::currentDateTime().toString("hh:mm:ss")
                    .arg(message));
}

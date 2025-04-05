#include "networkmanager.h"

#include <QDateTime>
#include <QMessageBox>
#include <QJsonObject>

NetworkManager::NetworkManager(QObject *parent)
{
    logMessage("Application started");
}

NetworkManager::~NetworkManager()
{
    delete m_server;
    delete m_client;
}

void NetworkManager::messageReceived(QString message)
{

}

void NetworkManager::handleNewMessage(const QJsonObject &message)
{
    // emits here signals ether to logic or for UI
}

void NetworkManager::onNewConnection()
{

}

void NetworkManager::onSocketDisconnected()
{

}

void NetworkManager::onSocketReadyRead()
{

}

void NetworkManager::createServer(const QString &host, quint16 port)
{
    if (host.isNull() || port == 0) {
        logMessage("Invalid host or port number");
        emit notifyPlayerWithMessageBox(tr("Invalid host or port."));
    }

    m_server = new Server(this);

    connect(m_server, &Server::newMessage, this, &NetworkManager::handleNewMessage);
    connect(m_server, &Server::logMessage, this, &NetworkManager::logMessage);

    if (!m_server->startListening(port)) {
        logMessage("Failed to start server: " + m_server->errorString());
        delete m_server;
        m_server = nullptr;
        emit notifyPlayerWithMessageBox(tr("This port is already listened by another server."));
        return;
    }

    logMessage("Server started listening port " + QString::number(port));

    emit notifyPlayerWithMessageBox(tr("The server has made successfully. Wait for clients"));
}

void NetworkManager::createClient(const QString &host, quint16 port)
{
    if (m_client) {
        logMessage("Invalid creation of client");
        emit notifyPlayerWithMessageBox(tr("Unsuccessful attempt to connect the client."));
        return;
    }

    m_client = new Client(this);
    connect(m_client, &Client::newMessage, this, &NetworkManager::handleNewMessage);
    connect(m_client, &Client::logMessage, this, &NetworkManager::logMessage);
    connect(m_client, &Client::connected, [this]() { logMessage("New client is connected!"); });

    m_client->connectToServer(QHostAddress(host), port);

    emit notifyPlayerWithMessageBox(tr("The client has successfully connected to the server."));
}

QJsonObject NetworkManager::createMessage(const QString &text)
{
    QJsonObject message;
    message["timestamp"] = QDateTime::currentDateTime().toString(Qt::ISODate);
    message["sender"] = m_isHost ? "Host" : "Client";
    message["content"] = text;
    return message;
}

void NetworkManager::logMessage(const QString &message)
{
    QString log = QString("[%1] %2")
                      .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
                      .arg(message);
    qDebug() << log;
}

void NetworkManager::sendMessage(const QString& message)
{
    if (message.isEmpty()) {
        return;
    }

    QJsonObject json = createMessage(message);
    if (m_isHost && m_server) {
        m_server->broadcast(json); // send to all clients
    } else if (m_client && m_client->isConnected()) {
        m_client->send(json);
    }
}

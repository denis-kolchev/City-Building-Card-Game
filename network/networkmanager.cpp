#include "networkmanager.h"
#include "jsons/jsondicerollresult.h"
#include "jsons/jsonfinishincomestate.h"

#include <QDateTime>
#include <QMessageBox>
#include <QJsonObject>

NetworkManager::NetworkManager(QObject *parent)
    : m_jsonFactory(new JsonMessageFactory())
    , m_isHost(false)
{
    logMessage("Application started");
}

NetworkManager::~NetworkManager()
{
    delete m_server;
    delete m_client;
    delete m_jsonFactory;
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

void NetworkManager::createClient(const QString &host, quint16 port)
{
    if (m_client) {
        logMessage("Invalid creation of client");
        emit notifyPlayerWithMessageBox(tr("Unsuccessful attempt to connect the client."));
        return;
    }

    setupClient(tr("New client is connected!"));
    m_client->connectToServer(QHostAddress(host), port);
    m_isHost = false;

    emit notifyPlayerWithMessageBox(tr("The client has successfully connected to the server."));
}

void NetworkManager::createServer(const QString &host, quint16 port, int playerCount)
{
    if (m_server) {
        logMessage(tr("Server is already running"));
        return;
    }

    if (host.isNull() || port == 0) {
        logMessage("Invalid host or port number");
        emit notifyPlayerWithMessageBox(tr("Invalid host or port."));
        return;
    }

    m_server = new Server(playerCount, this);

    //connect(m_server, &Server::newMessage, this, &NetworkManager::handleNewMessage);
    connect(m_server, &Server::logMessage, this, &NetworkManager::logMessage);

    if (!m_server->startListening(port)) {
        logMessage("Failed to start server: " + m_server->errorString());
        delete m_server;
        m_server = nullptr;
        emit notifyPlayerWithMessageBox(tr("This port is already listened by another server."));
        return;
    }

    // connects to its own 'client' to simplify logic of broadcast
    // Cleanup existing client if any
    if (m_client) {
        m_client->disconnectFromHost();
        delete m_client;
        m_client = nullptr;
    }

    setupClient(tr("Host client connected to local server"));

    m_client->connectToServer(QHostAddress::LocalHost, port);

    m_isHost = true;
    logMessage("Server started listening port " + QString::number(port));

    emit notifyPlayerWithMessageBox(tr("The server has made successfully. Wait for clients"));
}

void NetworkManager::broadcastDiceRollResult(int playerId, QVector<int> rolls)
{
    if (!m_client || !m_client->isConnected()) {
        return;
    }
    JsonDiceRollResult diceRollResult(playerId, rolls);
    m_client->send(diceRollResult.json());
}

void NetworkManager::broadcastFinishIncomeState(int playerId)
{
    if (!m_client || !m_client->isConnected()) {
        return;
    }
    JsonFinishIncomeState finishIncomeState(playerId);
    m_client->send(finishIncomeState.json());
}

void NetworkManager::sendMessage(const QString& message)
{
    if (message.isEmpty()) {
        return;
    }

    QJsonObject json = createMessage(message);
    if (m_isHost && m_server) {
        m_server->broadcast(json); // send to all clients
        logMessage(QString(tr("Host: %1").arg(message)));
    } else if (m_client && m_client->isConnected()) {
        m_client->send(json);
        logMessage(QString(tr("Client: %1").arg(message)));
    } else {
        logMessage(QString(tr("Server or client not connected!")));
    }
}

void NetworkManager::sendMessage(const AbstractJsonPtr& message)
{
    // TODO maybe should check that abstractJsonPtr isnt' empty
    auto json = message->json();

    if (m_isHost && m_server) {
        m_server->broadcast(json); // send to all clients
        logMessage(QString(tr("Host: %1").arg(message->type())));
    } else if (m_client && m_client->isConnected()) {
        m_client->send(json);
        logMessage(QString(tr("Client: %1").arg(message->type())));
    } else {
        logMessage(QString(tr("Server or client not connected!")));
    }
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

void NetworkManager::setupClient(const QString &connectedMessage)
{
    if (m_client) {
        logMessage("Client already exists, setup aborted.");
        return;
    }

    m_client = new Client(this);
    connect(m_client, &Client::newMessage, this, &NetworkManager::handleNewMessage);
    connect(m_client, &Client::logMessage, this, &NetworkManager::logMessage);
    connect(m_client, &Client::connected, [this, connectedMessage]() {
        logMessage(connectedMessage);
    });

    // Connect network signals with debug logging
    connect(m_client, &Client::networkGameInit, this, [this](int playerCount) {
        qDebug() << tr("client:networkGameInit: playerCount = %1").arg(playerCount);
        emit networkGameInit(playerCount);
    });

    connect(m_client, &Client::networkDiceRollResult, this, [this](int playerId, QVector<int> rollResult) {
        qDebug() << tr("client:networkDiceRollResult: playerId - %1, roll [%2, %3]")
        .arg(playerId)
            .arg(rollResult[0])
            .arg(rollResult[1]);
        emit networkDiceRollResult(playerId, rollResult);
    });

    connect(m_client, &Client::networkFinishIncomeState, this, &NetworkManager::networkFinishIncomeState);
}

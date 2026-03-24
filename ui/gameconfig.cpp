#include "gameconfig.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

GameConfig::GameConfig(const QJsonDocument& jsonDocument)
{
    Q_ASSERT(jsonDocument.isObject());
    const QJsonObject jsonObject = jsonDocument.object();
    parsePlayersCount(jsonObject);
    parsePlayersNames(jsonObject);
}

GameConfig::GameConfig(GameConfig&& other) noexcept
    : m_playersCount(other.m_playersCount)
{
}

GameConfig& GameConfig::operator=(GameConfig&& other) noexcept
{
    if (this != &other) {
        m_playersCount = other.m_playersCount;
    }

    return *this;
}

qsizetype GameConfig::getPlayersCount() const
{
    return m_playersCount;
}

QList<QString> GameConfig::getPlayersNames()
{
    return m_playersNames;
}


void GameConfig::parsePlayersCount(const QJsonObject& jsonObject)
{
    Q_ASSERT(jsonObject.contains("playersCount"));
    Q_ASSERT(jsonObject["playersCount"].isDouble());

    qsizetype count = jsonObject["playersCount"].toInt();

    Q_ASSERT(count >= 2 && count <= 4);

    m_playersCount = count;
}

void GameConfig::parsePlayersNames(const QJsonObject& jsonObject)
{
    Q_ASSERT(jsonObject.contains("players"));
    QJsonValue playersValue = jsonObject.value("players");

    Q_ASSERT(playersValue.isArray());
    QJsonArray playersArray = playersValue.toArray();

    QStringList playerNames;
    for (const QJsonValue& playerValue : playersArray) {
        Q_ASSERT(playerValue.isString());
        playerNames.append(playerValue.toString());
    }

    m_playersNames = playerNames;
}

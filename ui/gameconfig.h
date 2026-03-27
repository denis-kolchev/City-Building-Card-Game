#ifndef GAMECONFIG_H
#define GAMECONFIG_H

#include <QList>

class QJsonDocument;
class QJsonObject;
class QJsonArray;

/* Created only once, and
 * then might be rewriten only by moving.
 * It might be generated and sent to others vie network
 */

class GameConfig final
{
public:
    GameConfig(const QJsonDocument& jsonDocument);
    GameConfig(GameConfig&& other) noexcept;
    GameConfig& operator=(GameConfig&& other) noexcept;

    GameConfig(const GameConfig&) = delete;
    GameConfig& operator=(const GameConfig&) = delete;

    qsizetype getPlayersCount() const;
    QList<QString> getPlayersNames();

private:
    void parsePlayersCount(const QJsonObject& jsonObject);
    void extracted(QJsonArray &playersArray, QStringList &playerNames);
    void parsePlayersNames(const QJsonObject &jsonObject);

private:
    qsizetype m_playersCount = 2;
    QList<QString> m_playersNames;
};

#endif // GAMECONFIG_H

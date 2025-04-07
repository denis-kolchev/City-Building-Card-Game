#include "jsongameinit.h"

JsonGameInit::JsonGameInit(int playerCount)
    : m_playerCount(playerCount)
    , AbstractJsonStrategy("game_init")
{
}

QJsonObject JsonGameInit::json()
{
    return {
        {"type", type() },
        {"timestamp", QDateTime::currentDateTime().toString(Qt::ISODate)},
        {"data", QJsonObject {
                     {"player_count", m_playerCount }
                 }}

    };
}

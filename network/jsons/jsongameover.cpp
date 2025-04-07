#include "jsongameover.h"

JsonGameOver::JsonGameOver(int winnderId)
    : m_winnderId(winnderId)
    , AbstractJsonStrategy("game_over")
{
}

QJsonObject JsonGameOver::json()
{
    return {
        {"type", type() },
        {"timestamp", QDateTime::currentDateTime().toString(Qt::ISODate)},
        {"data", QJsonObject {
                     {"winnder_id", m_winnderId }
                 }}
    };
}

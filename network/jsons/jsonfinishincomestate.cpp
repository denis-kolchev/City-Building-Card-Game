#include "jsonfinishincomestate.h"

JsonFinishIncomeState::JsonFinishIncomeState(int playerId)
    : m_playerId(playerId)
    , AbstractJsonStrategy("finish_income_state")
{
}

QJsonObject JsonFinishIncomeState::json()
{
    return {
        {"type", type()},
        {"timestamp", QDateTime::currentDateTime().toString(Qt::ISODate)},
        {"data", QJsonObject {
                     {"player_id", m_playerId}
                 }}
    };
}

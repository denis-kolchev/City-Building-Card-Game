#include "initialplayercardshandler.h"
#include "../logic/player.h"

#include <QDebug>

InitialPlayerCardsHandler::InitialPlayerCardsHandler(QVector<std::shared_ptr<Player>>& players)
    : m_players(players)
{
}

void InitialPlayerCardsHandler::handleCardData(QVector<std::shared_ptr<Card>> data)
{
    for (const auto& card : data) {
        for (const auto& player : m_players) {
            player->addCard(card);
        }
    }
    qDebug() << "Initial player cards received and processed.";
}

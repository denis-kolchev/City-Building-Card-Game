#include "initialplayercardshandler.h"
#include "player.h"

#include <QDebug>

InitialPlayerCardsHandler::InitialPlayerCardsHandler(std::shared_ptr<Player>& player)
    : m_player(player)
{
}

void InitialPlayerCardsHandler::handleCardData(QVector<std::shared_ptr<Card>> data)
{
    for (const auto& card : data) {
        m_player->addCard(card);
    }

    qDebug() << "Initial player cards received and processed.";
}

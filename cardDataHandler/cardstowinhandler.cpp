#include "cardstowinhandler.h"

#include <QDebug>

CardsToWinHandler::CardsToWinHandler(QVector<std::shared_ptr<Card>>& cardsToWin)
    : m_cardsToWin(cardsToWin)
{
}

void CardsToWinHandler::handleCardData(QVector<std::shared_ptr<Card>> data)
{
    m_cardsToWin = data;
    qDebug() << "Cards to win received and processed.";
}

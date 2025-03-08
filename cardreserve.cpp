#include "cardreserve.h"

void CardReserve::addCard(std::shared_ptr<Card> card)
{
    m_cards.insert(card->title(), card);
}

void CardReserve::removeCard(const QString& cardName)
{
    m_cards.remove(cardName);
}

std::shared_ptr<Card> CardReserve::getCard(const QString& cardName) const
{
    return *m_cards.find(cardName);
}

void activateCard(const QString& cardName, Player& owner, Player& activePlayer, int diceRoll)
{

}

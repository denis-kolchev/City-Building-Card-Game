#include "bank.h"

Bank::Bank(QObject *parent)
    : m_cardInventory(new CardInventory())
    , QObject{parent}
{
}

Bank::~Bank()
{
}

void Bank::addCard(std::shared_ptr<Card> card)
{
    m_cardInventory->addCard(card);
    emit bankGetsCard(card); // notify UI about inventory changes
}

std::shared_ptr<Card> Bank::findCardById(CardId cardId)
{
    return m_cardInventory->findCardById(cardId);
}

void Bank::removeCard(std::shared_ptr<Card> card)
{
    m_cardInventory->removeCard(card);
    emit bankLoosesCard(card); // notify UI about inventory changes
}

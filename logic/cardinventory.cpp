#include "cardinventory.h"

void CardInventory::addCard(std::shared_ptr<Card> card)
{
    auto it = m_cards.find(card);
    if (it == m_cards.end()) {
        // creates a new stack
        m_cards.insert(card, 1);
        categorizeCard(card);
    } else {
        // places card on the existing stack
        m_cards[card] = it.value() + 1;
    }
}

void CardInventory::removeCard(std::shared_ptr<Card> card)
{
    auto it = m_cards.find(card);
    if (it == m_cards.end()) {
        return; // such card doesn't exist
    }

    if (it.value() > 1) {
        // removes a card from stack
        m_cards[card] = it.value() - 1;
    } else {
        // removes the whole stack of card
        m_cards.remove(card);
        uncategorizeCard(card);
    }
}

int CardInventory::countCard(std::shared_ptr<Card> card) const
{
    return m_cards.value(card, 0);
}

std::shared_ptr<Card> CardInventory::findCardById(CardId cardId) const
{
    for (auto it = m_cards.begin(); it != m_cards.end(); ++it) {
        if (it.key()->id() == cardId) {
            return it.key();
        }
    }

    return nullptr;
}

const QMap<std::shared_ptr<Card>, int>& CardInventory::getCards() const
{
    return m_cards;
}

const QMap<std::shared_ptr<Card>, int>& CardInventory::blueCards() const
{
    return m_blueCards;
}

const QMap<std::shared_ptr<Card>, int>& CardInventory::greenCards() const
{
    return m_greenCards;
}

const QMap<std::shared_ptr<Card>, int>& CardInventory::landmarks() const
{
    return m_landmarks;
}

const QMap<std::shared_ptr<Card>, int>& CardInventory::purpleCards() const
{
    return m_purpleCards;
}

const QMap<std::shared_ptr<Card>, int>& CardInventory::redCards() const
{
    return m_redCards;
}

void CardInventory::categorizeCard(std::shared_ptr<Card> card)
{
    if (card->activationValues().contains(0)) {
        auto it = m_landmarks.find(card);
        if (it != m_landmarks.end()) {
            m_landmarks[it.key()] = it.value() + 1;
        } else {
            m_landmarks.insert(card, 1);
        }
        return;
    }

    switch (card->type()) {
    case CardType::Dining:
        if (m_redCards.find(card) != m_redCards.end()) {
            m_redCards[card] = m_redCards.find(card).value() + 1;
        } else {
            m_redCards.insert(card, 1);
        }
        return;
    case CardType::Mining:
    case CardType::Agricultural:
    case CardType::Farm:
    case CardType::Ship:
        if (m_blueCards.find(card) != m_blueCards.end()) {
            m_blueCards[card] = m_blueCards.find(card).value() + 1;
        } else {
            m_blueCards.insert(card, 1);
        }
        return;
    case CardType::Shop:
    case CardType::Fruit:
    case CardType::Business:
    case CardType::Production:
        if (m_greenCards.find(card) != m_greenCards.end()) {
            m_greenCards[card] = m_greenCards.find(card).value() + 1;
        } else {
            m_greenCards.insert(card, 1);
        }
        return;
    case CardType::Landmark:
        if (m_purpleCards.find(card) != m_purpleCards.end()) {
            m_purpleCards[card] = m_purpleCards.find(card).value() + 1;
        } else {
            m_purpleCards.insert(card, 1);
        }
        return;
    }
}

void CardInventory::uncategorizeCard(std::shared_ptr<Card> card)
{
    m_landmarks.remove(card);
    m_redCards.remove(card);
    m_blueCards.remove(card);
    m_greenCards.remove(card);
    m_purpleCards.remove(card);
}


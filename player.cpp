#include "player.h"

Player::Player(const QString& name) : m_name(name), m_coins(START_COINS_NUMBER) {}

void Player::addCard(std::shared_ptr<Card> card) {
    m_cards.push_back(card);
}

void Player::addCoins(int amount) {
    m_coins += amount;
}

int Player::coins() const {
    return m_coins;
}

void Player::deductMoney(int amount) {
    m_coins -= amount;
}

std::vector<std::shared_ptr<Card>> Player::getCards() {
    return m_cards;
};

QString Player::name() const {
    return m_name;
}

void Player::triggerCards(int diceRoll, Player& activePlayer) {
    std::vector<std::shared_ptr<Card>> redCards, others;
    for (auto& card : m_cards) {
        if (card->type() == CardType::Dining) {
            redCards.push_back(card);
        }
    }

    for (auto& card : m_cards) {
        if (card->type() != CardType::Dining) {
            others.push_back(card);
        }
    }

    for (auto& card : redCards) {
        if (card->hasActivationValue(diceRoll)) {
            card->activate(*this, activePlayer, diceRoll);
        }
    }

    for (auto& card : others) {
        if (card->hasActivationValue(diceRoll)) {
            card->activate(*this, activePlayer, diceRoll);
        }
    }
}

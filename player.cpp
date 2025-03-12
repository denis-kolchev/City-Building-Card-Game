#include "player.h"

Player::Player(const QString& name) : m_name(name), m_coins(START_COINS_NUMBER) {}

void Player::addCard(std::shared_ptr<Card> card) {
    if (howManyCardsOfType(card) == 0) {
        m_cardsTable.insert(card, 0);
        return;
    }

    m_cardsTable[card]++;
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

QMap<std::shared_ptr<Card>, uchar> Player::getCardsTable() {
    return m_cardsTable;
}

uchar Player::howManyCardsOfType(std::shared_ptr<Card> card) {
    if (m_cardsTable.find(card) == m_cardsTable.end()) {
        return 0;
    }

    return m_cardsTable.find(card).value();
}

QString Player::name() const {
    return m_name;
}

void Player::triggerCards(int diceRoll, Player& activePlayer) {
    // To do: activate several cards if more then 1
    QMap<std::shared_ptr<Card>, uchar> redCardsTable, othersTable;
    for (auto it = m_cardsTable.begin(), ite = m_cardsTable.end(); it != ite; ++it) {
        if (it.key()->type() == CardType::Dining) {
            redCardsTable.insert(it.key(), it.value());
        } else {
            othersTable.insert(it.key(), it.value());
        }
    }

    for (auto it = redCardsTable.begin(), ite = redCardsTable.end(); it != ite; ++it) {
        for (uchar i = 0; i < it.value(); ++i) {
            if (it.key()->hasActivationValue(diceRoll)) {
                it.key()->activate(*this, activePlayer, diceRoll);
            }
        }
    }

    for (auto it = othersTable.begin(), ite = othersTable.end(); it != ite; ++it) {
        for (uchar i = 0; i < it.value(); ++i) {
            if (it.key()->hasActivationValue(diceRoll)) {
                it.key()->activate(*this, activePlayer, diceRoll);
            }
        }
    }

    //emit playerBalanceChanged(m_coins);
}

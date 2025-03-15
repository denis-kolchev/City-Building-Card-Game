#include "player.h"
#include <QtCore/qdebug.h>

Player::Player(const QString& name, QObject *parent)
    : m_name(name)
    , m_coins(START_COINS_NUMBER)
    , QObject(parent)
{
}

void Player::activateRollTwoDice() {
    emit hasRailwayStation();
}

void Player::addCard(std::shared_ptr<Card> card) {
    if (howManyCardsOfType(card) == 0) {
        m_cardsTable.insert(card, 1);
        return;
    }

    m_cardsTable[card]++;
}

void Player::addCoins(int amount) {
    m_coins += amount;
}

void Player::addLandmark(std::shared_ptr<Card> card) {
    m_landmarks.push_back(card);
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

QVector<std::shared_ptr<Card>> Player::getLandmarks() {
    return m_landmarks;
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
    qDebug() << "------ TRIGGERED " << diceRoll << " CARDS ------";
    for (auto it = m_landmarks.begin(), ite = m_landmarks.end(); it != ite; ++it) {
        qDebug() << "--- activated: " << it->get()->title();
        it->get()->activate(*this, activePlayer, diceRoll);
    }

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
                QString str;
                for (uchar value : it.key()->activationValues()) {
                    str += QString::number(value) + " ";
                }
                qDebug() << "--- activated: " << it.key()->title() << " " << str;
                it.key()->activate(*this, activePlayer, diceRoll);
            }
        }
    }

    for (auto it = othersTable.begin(), ite = othersTable.end(); it != ite; ++it) {
        for (uchar i = 0; i < it.value(); ++i) {
            if (it.key()->hasActivationValue(diceRoll)) {
                qDebug() << "--- activated: " << it.key()->title();
                it.key()->activate(*this, activePlayer, diceRoll);
            }
        }
    }
    qDebug() << "---------------------------------";

    //emit playerBalanceChanged(m_coins);
}

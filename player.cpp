#include "player.h"

Player::Player(const QString& name, int id, QObject *parent)
    : m_name(name)
    , m_id(id)
    , m_coins(START_COINS_NUMBER)
    , QObject(parent)
{
}

void Player::activateRerollDice()
{
    emit hasRadioTower();
}

void Player::activateRollTwoDice()
{
    emit hasRailwayStation();
}

void Player::activateOneMoreBuild()
{
    emit hasAmusementPark();
}

void Player::addCard(std::shared_ptr<Card> card)
{
    m_cardInventory->addCard(card);
    emit playerGetsCard(m_id, card);
}

void Player::addCoins(int amount)
{
    m_coins += amount;
    emit playerBalanceChanged(m_coins, m_id);
}

int Player::coins() const {
    return m_coins;
}

void Player::deductMoney(int amount)
{
    m_coins -= amount;
    emit playerBalanceChanged(m_coins, m_id);
}

int Player::id()
{
    return m_id;
}

QMap<std::shared_ptr<Card>, int> Player::getCards()
{
    return m_cardInventory->getCards();
}

const QMap<std::shared_ptr<Card>, int>& Player::getBlueCards() const
{
    return m_cardInventory->blueCards();
}

const QMap<std::shared_ptr<Card>, int>& Player::getGreenCards() const
{
    return m_cardInventory->greenCards();
}

const QMap<std::shared_ptr<Card>, int>& Player::getPurpleCards() const
{
    return m_cardInventory->purpleCards();
}

const QMap<std::shared_ptr<Card>, int>& Player::getRedCards() const
{
    return m_cardInventory->redCards();
}

const QMap<std::shared_ptr<Card>, int>& Player::getLandmarks()
{
    return m_cardInventory->landmarks();
}

int Player::howManyCardsOfType(std::shared_ptr<Card> card)
{
    auto cards = m_cardInventory->getCards();
    if (cards.contains(card)) {
        return 0;
    }

    return cards.find(card).value();
}

QString Player::name() const
{
    return m_name;
}

void Player::removeCard(std::shared_ptr<Card> card)
{
    m_cardInventory->removeCard(card);
    emit playerLoosesCard(m_id, card);
}

void Player::triggerCards(QVector<std::shared_ptr<Player>> players,
                          Player& activePlayer,
                          int dice1,
                          int dice2)
{
    const auto& landmarks = m_cardInventory->landmarks();
    for (auto it = landmarks.begin(), ite = landmarks.end(); it != ite; ++it) {
        for (int i = 0; i < it.value(); ++i) {
            it.key()->activate(players, *this, activePlayer, dice1, dice2);
        }
    }

    const auto& redCards = m_cardInventory->redCards();
    for (auto it = redCards.begin(), ite = redCards.end(); it != ite; ++it) {
        for (int i = 0; i < it.value(); ++i) {
            it.key()->activate(players, *this, activePlayer, dice1, dice2);
        }
    }

    const auto& greenCards = m_cardInventory->greenCards();
    for (auto it = greenCards.begin(), ite = greenCards.end(); it != ite; ++it) {
        for (int i = 0; i < it.value(); ++i) {
            it.key()->activate(players, *this, activePlayer, dice1, dice2);
        }
    }

    const auto& blueCards = m_cardInventory->blueCards();
    for (auto it = blueCards.begin(), ite = blueCards.end(); it != ite; ++it) {
        for (int i = 0; i < it.value(); ++i) {
            it.key()->activate(players, *this, activePlayer, dice1, dice2);
        }
    }

    const auto& purpleCards = m_cardInventory->purpleCards();
    for (auto it = purpleCards.begin(), ite = purpleCards.end(); it != ite; ++it) {
        for (int i = 0; i < it.value(); ++i) {
            it.key()->activate(players, *this, activePlayer, dice1, dice2);
        }
    }

    emit playerBalanceChanged(m_coins, m_id);
}

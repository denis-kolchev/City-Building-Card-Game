#include "player.h"

#include <QDebug>

Player::Player(QString name, int id, QObject *parent)
    : m_name(name)
    , m_id(id)
    , m_coins(START_COINS_NUMBER)
    , m_cardInventory(new CardInventory())
    , m_canRerollDice(false)
    , m_canPurchaseTwice(false)
    , QObject(parent)
{
}

Player::~Player()
{
    qDebug() << "Player is destroyed";
}

void Player::activateCards(QVector<std::shared_ptr<Player>>& players,
                          std::shared_ptr<Player>& activePlayer,
                          int dice1,
                          int dice2)
{
    const auto& landmarks = m_cardInventory->landmarks();
    for (auto it = landmarks.begin(), ite = landmarks.end(); it != ite; ++it) {
        for (int i = 0; i < it.value(); ++i) {
            qDebug() << "it value: " << it.value();
            it.key()->activate(players, *this, *activePlayer, dice1, dice2);
        }
    }

    const auto& redCards = m_cardInventory->redCards();
    for (auto it = redCards.begin(), ite = redCards.end(); it != ite; ++it) {
        for (int i = 0; i < it.value(); ++i) {
            it.key()->activate(players, *this, *activePlayer, dice1, dice2);
        }
    }

    const auto& greenCards = m_cardInventory->greenCards();
    for (auto it = greenCards.begin(), ite = greenCards.end(); it != ite; ++it) {
        for (int i = 0; i < it.value(); ++i) {
            it.key()->activate(players, *this, *activePlayer, dice1, dice2);
        }
    }

    const auto& blueCards = m_cardInventory->blueCards();
    for (auto it = blueCards.begin(), ite = blueCards.end(); it != ite; ++it) {
        for (int i = 0; i < it.value(); ++i) {
            it.key()->activate(players, *this, *activePlayer, dice1, dice2);
        }
    }

    const auto& purpleCards = m_cardInventory->purpleCards();
    for (auto it = purpleCards.begin(), ite = purpleCards.end(); it != ite; ++it) {
        for (int i = 0; i < it.value(); ++i) {
            it.key()->activate(players, *this, *activePlayer, dice1, dice2);
        }
    }

    emit playerBalanceChanged(m_id, m_coins);
}

void Player::addCard(std::shared_ptr<Card> card)
{
    m_cardInventory->addCard(card);
    emit playerGetsCard(m_id, card);
}

void Player::addCoins(int amount)
{
    m_coins += amount;
    emit playerBalanceChanged(m_id, m_coins);
}

int Player::balance() const {
    return m_coins;
}

bool Player::canRerollDice()
{
    return m_canRerollDice;
}

bool Player::canRollTwoDice()
{
    return m_canRollTwoDice;
}

bool Player::canPurchaseTwice()
{
    return m_canPurchaseTwice;
}

void Player::deductMoney(int amount)
{
    m_coins -= amount;
    emit playerBalanceChanged(m_id, m_coins);
}

int Player::id()
{
    return m_id;
}

std::shared_ptr<Card> Player::findCardById(CardId cardId)
{
    return m_cardInventory->findCardById(cardId);
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

bool Player::hasCard(CardId cardId)
{
    return m_cardInventory->findCardById(cardId) != nullptr;
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

void Player::setCanPurchaseTwice(bool canPurchaseTwice)
{
    m_canPurchaseTwice = canPurchaseTwice;
}

void Player::setCanRerollDice(bool canReroll)
{
    m_canRerollDice = canReroll;
}

void Player::setCanRollTwoDice(bool canRollTwoDice)
{
    m_canRollTwoDice = canRollTwoDice;
}

#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <QMap>
#include <QObject>

#include "cardinventory.h"
#include "icardcontainer.h"
#include "../logic/cards/card.h"

const int START_COINS_NUMBER = 3;

class Player : public QObject, public ICardContainer
{
    Q_OBJECT

public:
    Player(QString name, int id, QObject *parent = nullptr);

    ~Player();

    void activateCards(QVector<std::shared_ptr<Player>>& players,
                       std::shared_ptr<Player>& activePlayer,
                       int dice1,
                       int dice2);

    void addCard(std::shared_ptr<Card> card) override;

    void addCoins(int amount);

    int balance() const;

    bool canPurchaseTwice();

    bool canRerollDice();

    bool canRollTwoDice();

    void deductMoney(int amount);

    int id();

    std::shared_ptr<Card> findCardById(CardId cardId);

    QMap<std::shared_ptr<Card>, int> getCards();

    const QMap<std::shared_ptr<Card>, int>& getBlueCards() const;

    const QMap<std::shared_ptr<Card>, int>& getGreenCards() const;

    const QMap<std::shared_ptr<Card>, int>& getPurpleCards() const;

    const QMap<std::shared_ptr<Card>, int>& getRedCards() const;

    const QMap<std::shared_ptr<Card>, int>& getLandmarks();

    bool hasCard(CardId cardId);

    int howManyCardsOfType(std::shared_ptr<Card> card);

    QString name() const;

    void removeCard(std::shared_ptr<Card> card) override;

    void setCanPurchaseTwice(bool canPurchaseTwice);

    void setCanRerollDice(bool canReroll);

    void setCanRollTwoDice(bool canRollTwoDice);

signals:
    void playerGetsCard(int playerId, std::shared_ptr<Card> card);

    void playerLoosesCard(int playerId, std::shared_ptr<Card> card);

    void playerBalanceChanged(int playerId, int balance);

private:
    QString m_name;
    std::shared_ptr<CardInventory> m_cardInventory;
    int m_coins;
    int m_id;

    bool m_canPurchaseTwice;
    bool m_canRerollDice;
    bool m_canRollTwoDice;
};


#endif // PLAYER_H

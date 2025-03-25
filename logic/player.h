#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <QMap>
#include <QObject>

#include "cardinventory.h"
#include "../logic/cards/card.h"

const int START_COINS_NUMBER = 3;

class Player : public QObject {
    Q_OBJECT

public:
    Player(const QString& name, int id, QObject *parent = nullptr);

    ~Player();

    void activateRerollDice();

    void activateRollTwoDice();

    void activateOneMoreBuild();

    void addCard(std::shared_ptr<Card> card);

    void addCoins(int amount);

    int coins() const;

    void deductMoney(int amount);

    int id();

    QMap<std::shared_ptr<Card>, int> getCards();

    const QMap<std::shared_ptr<Card>, int>& getBlueCards() const;

    const QMap<std::shared_ptr<Card>, int>& getGreenCards() const;

    const QMap<std::shared_ptr<Card>, int>& getPurpleCards() const;

    const QMap<std::shared_ptr<Card>, int>& getRedCards() const;

    const QMap<std::shared_ptr<Card>, int>& getLandmarks();

    int howManyCardsOfType(std::shared_ptr<Card> card);

    QString name() const;

    void removeCard(std::shared_ptr<Card> card);

    void triggerCards(QVector<std::shared_ptr<Player>> players, Player& activePlayer, int dice1, int dice2);

signals:
    void playerGetsCard(int playerId, std::shared_ptr<Card> card);

    void playerLoosesCard(int playerId, std::shared_ptr<Card> card);

    void hasAmusementPark();

    void hasRadioTower();

    void hasRailwayStation();

    void playerBalanceChanged(int balance, int playerId);

private:
    QString m_name;
    std::shared_ptr<CardInventory> m_cardInventory;
    int m_coins;
    int m_id;
};


#endif // PLAYER_H

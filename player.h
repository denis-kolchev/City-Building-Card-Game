#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <QMap>

#include "cards/card.h"

const int START_COINS_NUMBER = 3;

class Player {
public:
    Player(const QString& name);

    void addCard(std::shared_ptr<Card> card);

    void addCoins(int amount);

    int coins() const;

    void deductMoney(int amount);

    QMap<std::shared_ptr<Card>, uchar> getCardsTable();

    uchar howManyCardsOfType(std::shared_ptr<Card> card);

    QString name() const;

    void triggerCards(int diceRoll, Player& activePlayer);

private:
    QMap<std::shared_ptr<Card>, uchar> m_cardsTable;
    QString m_name;
    int m_coins;
};


#endif // PLAYER_H

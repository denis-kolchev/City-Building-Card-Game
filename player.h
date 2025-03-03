#ifndef PLAYER_H
#define PLAYER_H

#include <QString>

#include "cards/card.h"

const int START_COINS_NUMBER = 3;

class Player {
public:
    Player(const QString& name);

    void addCard(std::shared_ptr<Card> card);

    void addCoins(int amount);

    int coins() const;

    void deductMoney(int amount);

    std::vector<std::shared_ptr<Card>> getCards();

    QString name() const;

    void triggerCards(int diceRoll, Player& activePlayer);

private:
    std::vector<std::shared_ptr<Card>> m_cards;
    QString m_name;
    int m_coins;
};


#endif // PLAYER_H

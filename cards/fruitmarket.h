#ifndef FRUITMARKET_H
#define FRUITMARKET_H

#include "card.h"
#include "../player.h"

#include <QDebug>

class FruitMarket : public Card {
public:
    FruitMarket(const QString& title,
                const QString& description,
                const QString& imagePath,
                const QSet<uchar>& activationValues,
                CardType type,
                uchar pack,
                uchar price);

    void activate(Player& owner, Player& activePlayer, int diceRoll) override;
};

#endif // FRUITMARKET_H

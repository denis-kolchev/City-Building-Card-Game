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
                uchar price,
                uchar id);

    void activate(QVector<std::shared_ptr<Player>> players, Player& owner, Player& activePlayer, uchar dice1, uchar dice2) override;
};

#endif // FRUITMARKET_H

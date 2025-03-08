#ifndef FURNITUREFACTORY_H
#define FURNITUREFACTORY_H

#include "card.h"
#include "../player.h"

#include <QDebug>

class FurnitureFactory : public Card {
public:
    FurnitureFactory(const QString& title,
                     const QString& description,
                     const QString& imagePath,
                     const QSet<uchar>& activationValues,
                     CardType type,
                     uchar pack,
                     uchar price);

    void activate(Player& owner, Player& activePlayer, int diceRoll) override;
};

#endif // FURNITUREFACTORY_H

#ifndef RADIOTOWER_H
#define RADIOTOWER_H

#include "card.h"
#include "../player.h"

#include <QDebug>

class RadioTower : public Card {
public:
    RadioTower(const QString& title,
               const QString& description,
               const QString& imagePath,
               const QSet<uchar>& activationValues,
               CardType type,
               uchar pack,
               uchar price);

    void activate(Player& owner, Player& activePlayer, int diceRoll) override;
};

#endif // RADIOTOWER_H

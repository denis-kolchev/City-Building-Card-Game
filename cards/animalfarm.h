#ifndef ANIMALFARM_H
#define ANIMALFARM_H

#include "card.h"
#include "../player.h"

#include <QDebug>

class AnimalFarm : public Card {
public:
    AnimalFarm(const QString& title,
               const QString& description,
               const QString& imagePath,
               const QSet<uchar>& activationValues,
               CardType type,
               uchar pack,
               uchar price);

    void activate(Player& owner, Player& activePlayer, int diceRoll) override;
};

#endif // ANIMALFARM_H

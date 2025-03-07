#ifndef CAFE_H
#define CAFE_H

#include "card.h"
#include "../player.h"

#include <QDebug>

class Cafe : public Card {
public:
    Cafe(const QString& name, const QString& description, CardType type, int activationValue);

    void activate(Player& owner, Player& activePlayer, int diceRoll) override;
};

#endif // CAFE_H

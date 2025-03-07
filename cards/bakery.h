#ifndef BAKERY_H
#define BAKERY_H

#include "card.h"
#include "../player.h"

#include <QDebug>

class Bakery : public Card {
public:
    Bakery(const QString& name, const QString& description, CardType type, int activationValue);

    void activate(Player& owner, Player& activePlayer, int diceRoll) override;
};

#endif // BAKERY_H

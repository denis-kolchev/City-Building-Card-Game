#ifndef WHEATFIELD_H
#define WHEATFIELD_H

#include "card.h"
#include "../player.h"

#include <QDebug>

class WheatField : public Card {
public:
    WheatField(const QString& name, CardType type, int activationValue);

    void activate(Player& owner, Player& activePlayer, int diceRoll) override;
};

#endif // WHEATFIELD_H

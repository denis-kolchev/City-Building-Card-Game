#ifndef SHOPPINGMALL_H
#define SHOPPINGMALL_H

#include "card.h"
#include "../player.h"

#include <QDebug>

class ShoppingMall : public Card {
public:
    ShoppingMall(const QString& name, CardType type, int activationValue);

    void activate(Player& owner, Player& activePlayer, int diceRoll) override;
};

#endif // SHOPPINGMALL_H

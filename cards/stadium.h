#ifndef STADIUM_H
#define STADIUM_H

#include "card.h"
#include "../player.h"

#include <QDebug>

class Stadium : public Card {
public:
    Stadium(const QString& title,
                  const QString& description,
                  const QString& imagePath,
                  const QSet<uchar>& activationValues,
                  CardType type,
                  uchar pack,
                  uchar price);

    void activate(Player& owner, Player& activePlayer, int diceRoll) override;
};

#endif // STADIUM_H

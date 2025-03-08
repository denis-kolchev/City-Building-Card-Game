#ifndef BUSINESSCENTER_H
#define BUSINESSCENTER_H

#include "card.h"
#include "../player.h"

#include <QDebug>

class BusinessCenter : public Card {
public:
    BusinessCenter(const QString& title,
                   const QString& description,
                   const QString& imagePath,
                   const QSet<uchar>& activationValues,
                   CardType type,
                   uchar pack,
                   uchar price);

    void activate(Player& owner, Player& activePlayer, int diceRoll) override;
};

#endif // BUSINESSCENTER_H

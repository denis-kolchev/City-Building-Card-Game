#ifndef CARDRESERVE_H
#define CARDRESERVE_H

#include "cards/card.h"

#include <QMap>

/*

How many cards of each out there

title=Wheat Field - 6
title=Animal Farm - 6
title=Bakery - 6
title=Cafe - 6
title=Shop - 6
title=Forest - 6
title=Stadium - 5
title=TV Center - 5
title=Business Center - 5
title=Cheese Factory - 6
title=Furniture Factory - 6
title=Mine - 6
title=Restaurant - 6
title=Apple Orchard - 6
title=Fruit Marketå - 6

Feels like there is should be file called Game Rools

*/

class CardReserve {
public:
    CardReserve();

    ~CardReserve();

    void addCard(std::shared_ptr<Card> card);

    uchar coundCards(std::shared_ptr<Card> card);

    void removeCard(std::shared_ptr<Card> card);

    void activateCard(const QString& cardName, Player& owner, Player& activePlayer, int diceRoll);

private:
    QMap<std::shared_ptr<Card>, uchar> m_cards;
};

#endif // CARDRESERVE_H

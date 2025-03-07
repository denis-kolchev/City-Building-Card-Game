#ifndef CARDRESERVE_H
#define CARDRESERVE_H

#include "cards/card.h"

#include <QMap>

class CardReserve {
public:
    CardReserve();

    ~CardReserve();

    void addCard(std::shared_ptr<Card> card);

    void removeCard(const QString& cardName);

    std::shared_ptr<Card> getCard(const QString& cardName) const;

    void activateCard(const QString& cardName, Player& owner, Player& activePlayer, int diceRoll);

private:
    QMap<QString, std::shared_ptr<Card>> m_cards;
};

#endif // CARDRESERVE_H

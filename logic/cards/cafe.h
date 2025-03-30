#ifndef CAFE_H
#define CAFE_H

#include "card.h"
#include "../player.h"

#include <QDebug>

class Cafe : public Card {
public:
    Cafe(const QString& title,
         const QString& description,
         const QString& imagePath,
         const QSet<int>& activationValues,
         CardType type,
         int pack,
         int price,
         CardId id);

    void activate(QVector<std::shared_ptr<Player>>& players,
                  Player& owner,
                  Player& activePlayer,
                  int dice1,
                  int dice2);
};

#endif // CAFE_H

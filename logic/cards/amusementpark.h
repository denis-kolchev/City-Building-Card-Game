#ifndef AMUSEMENTPARK_H
#define AMUSEMENTPARK_H

#include "card.h"
#include "../player.h"

#include <QDebug>

class AmusementPark : public Card {
public:
    AmusementPark(const QString& title,
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

#endif // AMUSEMENTPARK_H

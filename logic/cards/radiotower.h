#ifndef RADIOTOWER_H
#define RADIOTOWER_H

#include "card.h"
#include "../player.h"

#include <QDebug>

class RadioTower : public Card {
public:
    RadioTower(const QString& title,
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

#endif // RADIOTOWER_H

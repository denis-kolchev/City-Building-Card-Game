#ifndef SHOP_H
#define SHOP_H

#include "card.h"
#include "../player.h"

#include <QDebug>

class Shop : public Card {
public:
    Shop(const QString& title,
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

#endif // SHOP_H

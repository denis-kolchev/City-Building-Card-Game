#ifndef BAKERY_H
#define BAKERY_H

#include "card.h"
#include "../player.h"

#include <QDebug>

class Bakery : public Card {
public:
    Bakery(const QString& title,
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

#endif // BAKERY_H

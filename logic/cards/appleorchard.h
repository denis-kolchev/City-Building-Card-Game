#ifndef APPLEORCHARD_H
#define APPLEORCHARD_H

#include "card.h"
#include "../player.h"

#include <QDebug>

class AppleOrchard : public Card {
public:
    AppleOrchard(const QString& title,
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

#endif // APPLEORCHARD_H

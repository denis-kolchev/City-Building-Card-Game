#ifndef CHEESEFACTORY_H
#define CHEESEFACTORY_H

#include "card.h"
#include "../player.h"

#include <QDebug>

class CheeseFactory : public Card {
public:
    CheeseFactory(const QString& title,
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

#endif // CHEESEFACTORY_H

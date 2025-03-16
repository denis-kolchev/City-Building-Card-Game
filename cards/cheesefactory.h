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
                  const QSet<uchar>& activationValues,
                  CardType type,
                  uchar pack,
                  uchar price);

    void activate(QVector<std::shared_ptr<Player>> players, Player& owner, Player& activePlayer, int diceRoll) override;
};

#endif // CHEESEFACTORY_H

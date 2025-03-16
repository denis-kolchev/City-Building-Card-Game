#ifndef STADIUM_H
#define STADIUM_H

#include "card.h"
#include "../player.h"

#include <QDebug>

class Stadium : public Card {
public:
    Stadium(const QString& title,
                  const QString& description,
                  const QString& imagePath,
                  const QSet<uchar>& activationValues,
                  CardType type,
                  uchar pack,
                  uchar price);

    void activate(QVector<std::shared_ptr<Player>> players, Player& owner, Player& activePlayer, uchar dice1, uchar dice2) override;
};

#endif // STADIUM_H

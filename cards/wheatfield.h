#ifndef WHEATFIELD_H
#define WHEATFIELD_H

#include "card.h"
#include "../player.h"

#include <QDebug>

class WheatField : public Card {
public:
    WheatField(const QString& title,
               const QString& description,
               const QString& imagePath,
               const QSet<uchar>& activationValues,
               CardType type,
               uchar pack,
               uchar price);

    void activate(QVector<std::shared_ptr<Player>> players, Player& owner, Player& activePlayer, int diceRoll) override;
};

#endif // WHEATFIELD_H

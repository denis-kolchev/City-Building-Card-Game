#ifndef TVCENTER_H
#define TVCENTER_H

#include "card.h"
#include "../player.h"

#include <QDebug>

class TVCenter : public Card {
public:
    TVCenter(const QString& title,
             const QString& description,
             const QString& imagePath,
             const QSet<uchar>& activationValues,
             CardType type,
             uchar pack,
             uchar price,
             uchar id);

    void activate(QVector<std::shared_ptr<Player>> players, Player& owner, Player& activePlayer, uchar dice1, uchar dice2) override;
};

#endif // TVCENTER_H

#ifndef CARDFACTORY_H
#define CARDFACTORY_H

#include "logic/cards/card.h"

#include <memory>

class CardFactory
{
public:
    CardFactory();

    std::shared_ptr<Card> createCard(const QString& title,
                                     const QString& description,
                                     const QString& imagePath,
                                     const QSet<uchar>& activationValues,
                                     CardType type,
                                     uchar pack,
                                     uchar price,
                                     uchar id);
};

#endif // CARDFACTORY_H

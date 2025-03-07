#ifndef CARDFACTORY_H
#define CARDFACTORY_H

#include "cards/card.h"

#include <memory>

class CardFactory
{
public:
    CardFactory();

    std::shared_ptr<Card> createCard(const QString& name,
                                     const QString& description,
                                     CardType type,
                                     int activationValue);
};

#endif // CARDFACTORY_H

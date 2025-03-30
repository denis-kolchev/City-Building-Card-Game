#ifndef CARDDATAHANDLER_H
#define CARDDATAHANDLER_H

#include "../logic/cards/card.h"

// Strategy Pattern
class CardDataHandler {
public:
    virtual ~CardDataHandler() = default;

    virtual void handleCardData(QVector<std::shared_ptr<Card>> data) = 0;
};

#endif // CARDDATAHANDLER_H

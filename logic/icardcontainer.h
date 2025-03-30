#ifndef ICARDCONTAINER_H
#define ICARDCONTAINER_H

#include <memory>
#include "cards/card.h"

class ICardContainer
{
public:
    virtual ~ICardContainer() = default;

    virtual void addCard(std::shared_ptr<Card> card) = 0;

    virtual void removeCard(std::shared_ptr<Card> card) = 0;
};

#endif // ICARDCONTAINER_H

#include "cardfactory.h"
#include "cards/bakery.h"
#include "cards/cafe.h"
#include "cards/shoppingmall.h"
#include "cards/wheatfield.h"

CardFactory::CardFactory() {}

std::shared_ptr<Card> CardFactory::createCard(const QString& name,
                                              const QString& description,
                                              CardType type,
                                              int activationValue)
{
    if (name == "Wheat Field") {
        return std::make_shared<WheatField>(name, description, type, activationValue);
    } else if (name == "Mall") {
        return std::make_shared<ShoppingMall>(name, description, type, activationValue);
    } else if (name == "Bakery") {
        return std::make_shared<Bakery>(name, description, type, activationValue);
    } else if (name == "Cafe") {
        return std::make_shared<Cafe>(name, description, type, activationValue);
    }
    return nullptr;
}

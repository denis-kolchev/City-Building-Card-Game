#include "cardfactory.h"
#include "logic/cards/amusementpark.h"
#include "logic/cards/animalfarm.h"
#include "logic/cards/appleorchard.h"
#include "logic/cards/bakery.h"
#include "logic/cards/businesscenter.h"
#include "logic/cards/cafe.h"
#include "logic/cards/cheesefactory.h"
#include "logic/cards/forest.h"
#include "logic/cards/fruitmarket.h"
#include "logic/cards/furniturefactory.h"
#include "logic/cards/mine.h"
#include "logic/cards/radiotower.h"
#include "logic/cards/railwaystation.h"
#include "logic/cards/restaurant.h"
#include "logic/cards/shop.h"
#include "logic/cards/shoppingmall.h"
#include "logic/cards/stadium.h"
#include "logic/cards/tvcenter.h"
#include "logic/cards/wheatfield.h"

CardFactory::CardFactory() {}

std::shared_ptr<Card> CardFactory::createCard(const QString& title,
                                              const QString& description,
                                              const QString& imagePath,
                                              const QSet<int>& activationValues,
                                              CardType type,
                                              int pack,
                                              int price,
                                              CardId id)
{
    if (title == "Railway Station") {
        return std::make_shared<RailwayStation>(title, description, imagePath, activationValues, type, pack, price, id);
    } else if (title == "Shopping Mall") {
        return std::make_shared<ShoppingMall>(title, description, imagePath, activationValues, type, pack, price, id);
    } else if (title == "Amusement Park") {
        return std::make_shared<AmusementPark>(title, description, imagePath, activationValues, type, pack, price, id);
    } else if (title == "Radio Tower") {
        return std::make_shared<RadioTower>(title, description, imagePath, activationValues, type, pack, price, id);
    } else if (title == "Wheat Field") {
        return std::make_shared<WheatField>(title, description, imagePath, activationValues, type, pack, price, id);
    } else if (title == "Animal Farm") {
        return std::make_shared<AnimalFarm>(title, description, imagePath, activationValues, type, pack, price, id);
    } else if (title == "Bakery") {
        return std::make_shared<Bakery>(title, description, imagePath, activationValues, type, pack, price, id);
    } else if (title == "Cafe") {
        return std::make_shared<Cafe>(title, description, imagePath, activationValues, type, pack, price, id);
    } else if (title == "Shop") {
        return std::make_shared<Shop>(title, description, imagePath, activationValues, type, pack, price, id);
    } else if (title == "Forest") {
        return std::make_shared<Forest>(title, description, imagePath, activationValues, type, pack, price, id);
    } else if (title == "Stadium") {
        return std::make_shared<Stadium>(title, description, imagePath, activationValues, type, pack, price, id);
    } else if (title == "TV Center") {
        return std::make_shared<TVCenter>(title, description, imagePath, activationValues, type, pack, price, id);
    } else if (title == "Business Center") {
        return std::make_shared<BusinessCenter>(title, description, imagePath, activationValues, type, pack, price, id);
    } else if (title == "Cheese Factory") {
        return std::make_shared<CheeseFactory>(title, description, imagePath, activationValues, type, pack, price, id);
    } else if (title == "Furniture Factory") {
        return std::make_shared<FurnitureFactory>(title, description, imagePath, activationValues, type, pack, price, id);
    } else if (title == "Mine") {
        return std::make_shared<Mine>(title, description, imagePath, activationValues, type, pack, price, id);
    } else if (title == "Restaurant") {
        return std::make_shared<Restaurant>(title, description, imagePath, activationValues, type, pack, price, id);
    } else if (title == "Apple Orchard") {
        return std::make_shared<AppleOrchard>(title, description, imagePath, activationValues, type, pack, price, id);
    } else if (title == "Fruit Market") {
        return std::make_shared<FruitMarket>(title, description, imagePath, activationValues, type, pack, price, id);
    } else {
        return nullptr;
    }
}

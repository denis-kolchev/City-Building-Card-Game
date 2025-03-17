#include "cardfactory.h"
#include "cards/amusementpark.h"
#include "cards/animalfarm.h"
#include "cards/appleorchard.h"
#include "cards/bakery.h"
#include "cards/businesscenter.h"
#include "cards/cafe.h"
#include "cards/cheesefactory.h"
#include "cards/forest.h"
#include "cards/fruitmarket.h"
#include "cards/furniturefactory.h"
#include "cards/mine.h"
#include "cards/radiotower.h"
#include "cards/railwaystation.h"
#include "cards/restaurant.h"
#include "cards/shop.h"
#include "cards/shoppingmall.h"
#include "cards/stadium.h"
#include "cards/tvcenter.h"
#include "cards/wheatfield.h"

CardFactory::CardFactory() {}

std::shared_ptr<Card> CardFactory::createCard(const QString& title,
                                              const QString& description,
                                              const QString& imagePath,
                                              const QSet<uchar>& activationValues,
                                              CardType type,
                                              uchar pack,
                                              uchar price,
                                              uchar id)
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

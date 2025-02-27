#include "cardreserve.h"

CardReserve::CardReserve(QObject *parent)
    : QObject{parent}
{
    // ------- Base Game Cards -------
    // >> Landmarks <<
    m_landmark.insert(new Card("Railway Station",
                                "You can roll 2 dice instead of 1.",
                                IncomeType::Landmark,
                                CardType::Landmark,
                                ActionSource::RailwayStation,
                                4,
                                {0}));
    m_landmark.insert(new Card("Shopping Mall",
                               "Each of your businesses with the coffee shop and store symbol brings you 1 coin more.",
                               IncomeType::Landmark,
                               CardType::Landmark,
                               ActionSource::ShoppingMall,
                               10,
                               {0}));
    /*

    baseGameCardsInfo.push_back(new Card("Amusement Park",
                                             "If the dice show a double, make another move.",
                                             CardVariation::Landmark,
                                             IncomeType::None,
                                             CardType::None,
                                             16,
                                             {0}));
    baseGameCardsInfo.push_back(new Card("Radio Tower",
                                             "You can reroll the dice once.",
                                             CardVariation::Landmark,
                                             IncomeType::None,
                                             CardType::None,
                                             22,
                                             {0}));

    // >> Builds <<
    baseGameCardsInfo.push_back(new Card("Wheat Field",
                                             "Take 1 coin from the bank.",
                                             CardVariation::Build,
                                             IncomeType::Passive,
                                             CardType::Agricultiral,
                                             1,
                                             {1}));
    baseGameCardsInfo.push_back(new Card("Farm",
                                             "Take 1 coin from the bank.",
                                             CardVariation::Build,
                                             IncomeType::Passive,
                                             CardType::Farm,
                                             1,
                                             {2}));
    baseGameCardsInfo.push_back(new Card("Bakery",
                                             "Take 1 coin from the bank.",
                                             CardVariation::Build,
                                             IncomeType::Turn,
                                             CardType::Shop,
                                             1,
                                             {2, 3})); // 2-3!!!
    baseGameCardsInfo.push_back(new Card("Cafe",
                                             "Take 1 coin from the player who rolled the dice.",
                                             CardVariation::Build,
                                             IncomeType::Penalty,
                                             CardType::Cafe,
                                             2,
                                             {3}));
    baseGameCardsInfo.push_back(new Card("Shop",
                                             "Take 3 coins from the bank.",
                                             CardVariation::Build,
                                             IncomeType::Turn,
                                             CardType::Shop,
                                             2,
                                             {4}));
    baseGameCardsInfo.push_back(new Card("Forest",
                                             "Take 1 coin from the bank.",
                                             CardVariation::Build,
                                             IncomeType::Passive,
                                             CardType::Mining,
                                             3,
                                             {5}));
    baseGameCardsInfo.push_back(new Card("Stadium",
                                             "Take 2 coins from each player.",
                                             CardVariation::Build,
                                             IncomeType::Tribute,
                                             CardType::Landmark,
                                             6,
                                             {6}));
    baseGameCardsInfo.push_back(new Card("TV Center",
                                             "Take 5 coins from any one player.",
                                             CardVariation::Build,
                                             IncomeType::Tribute,
                                             CardType::Landmark,
                                             7,
                                             {6}));
    baseGameCardsInfo.push_back(new Card("Business Center",
                                             "You can exchange 1 enterprise card with another player. You cannot exchange cards with the landmark symbol.",
                                             CardVariation::Build,
                                             IncomeType::Tribute,
                                             CardType::Landmark,
                                             8,
                                             {6}));
    baseGameCardsInfo.push_back(new Card("Cheese Factory",
                                             "Take 3 coins from the bank for each business you own with a farm symbol.",
                                             CardVariation::Build,
                                             IncomeType::Turn,
                                             CardType::Production,
                                             5,
                                             {7}));
    baseGameCardsInfo.push_back(new Card("Furniture Factory",
                                             "Take 3 coins from the bank for each business you own with a mining symbol.",
                                             CardVariation::Build,
                                             IncomeType::Turn,
                                             CardType::Production,
                                             3,
                                             {8}));
    baseGameCardsInfo.push_back(new Card("Mine",
                                             "Take 5 coins from the bank.",
                                             CardVariation::Build,
                                             IncomeType::Passive,
                                             CardType::Mining,
                                             6,
                                             {9}));
    baseGameCardsInfo.push_back(new Card("Restaurant",
                                             "Take 2 coins from the player who rolled the dice.",
                                             CardVariation::Build,
                                             IncomeType::Penalty,
                                             CardType::Cafe,
                                             3,
                                             {9, 10}));

    baseGameCardsInfo.push_back(new Card("Apple Orchard",
                                             "Take 3 coins from the bank.",
                                             CardVariation::Build,
                                             IncomeType::Passive,
                                             CardType::Agricultiral,
                                             3,
                                             {10}));
    baseGameCardsInfo.push_back(new Card("Fruit Market",
                                             "Take 2 coins from the bank for each business you own with a agricultiral symbol.",
                                             CardVariation::Build,
                                             IncomeType::Turn,
                                             CardType::Fruit,
                                             2,
                                             {11, 12}));

    // ------- Game Extension Cards -------
    // >> Landmarks <<
    extensionCardsInfo.push_back(new Card("Town Hall",
                                              "If you have no coins, take 1 coin from the bank.",
                                              CardVariation::Landmark,
                                              IncomeType::None,
                                              CardType::None,
                                              0,
                                              {0}));
    extensionCardsInfo.push_back(new Card("Sea Port",
                                              "If the dice roll a \"10\" or higher, you may add \"2\" to the result of the roll.",
                                              CardVariation::Landmark,
                                              IncomeType::None,
                                              CardType::None,
                                              2,
                                              {0}));
    extensionCardsInfo.push_back(new Card("Airport",
                                              "If you haven't built anything this turn, take 10 coins from the bank.",
                                              CardVariation::Landmark,
                                              IncomeType::None,
                                              CardType::None,
                                              30,
                                              {0}));

    // >> Builds <<
    extensionCardsInfo.push_back(new Card("Sushi Bar",
                                              "If you have \"Seaport\", take 3 coins from the player who rolled the dice.",
                                              CardVariation::Build,
                                              IncomeType::Penalty,
                                              CardType::Cafe,
                                              2,
                                              {1}));
    extensionCardsInfo.push_back(new Card("Flower Garden",
                                              "Take 1 coin from the bank.",
                                              CardVariation::Build,
                                              IncomeType::Passive,
                                              CardType::Agricultiral,
                                              2,
                                              {4}));
    extensionCardsInfo.push_back(new Card("Flower Shop",
                                              "Take 1 coin from the bank for each \"Flower Garden\" you own.",
                                              CardVariation::Build,
                                              IncomeType::Turn,
                                              CardType::Shop,
                                              1,
                                              {6}));
    extensionCardsInfo.push_back(new Card("Pizzeria",
                                              "Take 1 coin from the player who rolled the dice.",
                                              CardVariation::Build,
                                              IncomeType::Penalty,
                                              CardType::Cafe,
                                              1,
                                              {7}));
    extensionCardsInfo.push_back(new Card("Publishing House",
                                              "Take 1 coin from each player for each of their businesses with a cafe or shop symbol.",
                                              CardVariation::Build,
                                              IncomeType::Tribute,
                                              CardType::Landmark,
                                              5,
                                              {7}));
    extensionCardsInfo.push_back(new Card("Fishing Boat",
                                              "If you have \"Sea Port\", take 3 coins from the bank.",
                                              CardVariation::Build,
                                              IncomeType::Passive,
                                              CardType::Ship,
                                              2,
                                              {8}));
    extensionCardsInfo.push_back(new Card("Snack Bar",
                                              "Take 1 coin from the player who rolled the dice.",
                                              CardVariation::Build,
                                              IncomeType::Penalty,
                                              CardType::Cafe,
                                              1,
                                              {8}));
    extensionCardsInfo.push_back(new Card("Tax Inspectorate",
                                              "Take half the coins from each player with 10 coins or more (rounded down).",
                                              CardVariation::Build,
                                              IncomeType::Tribute,
                                              CardType::Landmark,
                                              4,
                                              {8, 9}));

    extensionCardsInfo.push_back(new Card("Food Warehouse",
                                              "Take 2 coins from the bank for each of your businesses with a cafe symbol.",
                                              CardVariation::Build,
                                              IncomeType::Turn,
                                              CardType::Production,
                                              2,
                                              {12, 13}));

    extensionCardsInfo.push_back(new Card("Trawler",
                                              "The active player rolls 2 dice. If you have \"Seaport\", take as many coins from the bank as the dice show.",
                                              CardVariation::Build,
                                              IncomeType::Passive,
                                              CardType::Ship,
                                              5,
                                              {12, 13, 14}));

    // ------- Game Expansion Cards -------
    // >> Builds <<
    extensionCardsInfo.push_back(new Card("Supermarket",
                                              "Take 2 coins from the bank if you have no more than 1 landmark.",
                                              CardVariation::Build,
                                              IncomeType::Turn,
                                              CardType::Shop,
                                              0,
                                              {2}));

    expansionCardsInfo.push_back(new Card("Cornfield",
                                              "Take 1 coin from the bank if you have less than 1 landmark.",
                                              CardVariation::Build,
                                              IncomeType::Passive,
                                              CardType::Agricultiral,
                                              2,
                                              {3, 4}));

    expansionCardsInfo.push_back(new Card("Dismantling Company",
                                              "Turn your landmark card 1 face down. Once you do this, take 8 coins from the bank.",
                                              CardVariation::Build,
                                              IncomeType::Turn,
                                              CardType::Business,
                                              2,
                                              {4}));

    expansionCardsInfo.push_back(new Card("Prestigious Restaurant",
                                              "Take 5 coins from the player who rolled the dice if he has 2 or more landmarks.",
                                              CardVariation::Build,
                                              IncomeType::Penalty,
                                              CardType::Cafe,
                                              3,
                                              {5}));
    expansionCardsInfo.push_back(new Card("Credit Bank",
                                              "Give 2 coins to the bank. After building this enterprise, take 5 coins from the bank.",
                                              CardVariation::Build,
                                              IncomeType::Turn,
                                              CardType::Business,
                                              0,
                                              {5, 6}));

    expansionCardsInfo.push_back(new Card("Vineyard",
                                              "Take 3 coins from the bank.",
                                              CardVariation::Build,
                                              IncomeType::Passive,
                                              CardType::Agricultiral,
                                              3,
                                              {7}));
    expansionCardsInfo.push_back(new Card("Cleaning Company",
                                              "Choose 1 business without a landmark symbol. All businesses of this type built by all players are temporarily closed. Take 1 coin from the bank for each business temporarily closed by this effect.",
                                              CardVariation::Build,
                                              IncomeType::Tribute,
                                              CardType::Landmark,
                                              4,
                                              {8}));
    expansionCardsInfo.push_back(new Card("Transport Company",
                                              "Transfer 1 of your businesses without a landmark symbol to another player. Once you do this, take 4 coins from the bank.",
                                              CardVariation::Build,
                                              IncomeType::Turn,
                                              CardType::Business,
                                              2,
                                              {9, 10}));

    expansionCardsInfo.push_back(new Card("Venture Fund",
                                              "Take as many coins from each player as are on this card. At the end of each of your turns, you may place 1 of your coins on this card.",
                                              CardVariation::Build,
                                              IncomeType::Tribute,
                                              CardType::Landmark,
                                              1,
                                              {10}));

    expansionCardsInfo.push_back(new Card("Beverage Factory",
                                              "Take as many coins from the bank as there are businesses with the cafe symbol built by all players.",
                                              CardVariation::Build,
                                              IncomeType::Turn,
                                              CardType::Production,
                                              5,
                                              {11}));
    expansionCardsInfo.push_back(new Card("Park",
                                              "Collect all players' coins and distribute them equally among all players. If you can't distribute them equally, take the missing number of coins from the bank, and then distribute the coins.",
                                              CardVariation::Build,
                                              IncomeType::Tribute,
                                              CardType::Landmark,
                                              3,
                                              {11, 12, 13}));

    expansionCardsInfo.push_back(new Card("Private Bar",
                                              "Take all coins from the player who rolled the dice if he has 3 or more landmarks.",
                                              CardVariation::Build,
                                              IncomeType::Penalty,
                                              CardType::Cafe,
                                              4,
                                              {12, 13, 14}));

*/
}

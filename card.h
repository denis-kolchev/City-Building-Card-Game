#ifndef CARD_H
#define CARD_H

#include <QObject>
#include <QSet>

enum class IncomeType
{
    Landmark,
    Passive,
    Turn,
    Penalty,
    Tribute,
};

enum class CardType
{
    Shop,
    Dining, // Dining?
    Agricultiral,
    Landmark,
    Farm,
    Mining,
    Production,
    Fruit,
    Ship,
    Business
};

enum class ActionSource
{
    RailwayStation,
    ShoppingMall,
    AmusementPark,
    RadioTower,
    WheatField,
    Farm,
    Bakery,
    Cafe,
    Shop,
    Forest,
    Stadium,
    TVCenter,
    BusinessCenter,
    CheeseFactory,
    FurnitureFactory,
    Mine,
    Restaurant,
    AppleOrchard,
    FruitMarket,
    TownHall,
    SeaPort,
    Airport,
    SushiBar,
    FlowerGarden,
    FlowerShop,
    Pizzeria,
    PublishingHouse,
    FishingBoat,
    SnackBar,
    TaxInspectorate,
    FoodWarehouse,
    Trawler,
    Supermarket,
    Cornfield,
    DismantlingCompany,
    PrestigiousRestaurant,
    CreditBank,
    Vineyard,
    CleaningCompany,
    TransportCompany,
    VentureFund,
    BeverageFactory,
    Park,
    PrivateBar,
};

class Player;

class Card : public QObject
{
    Q_OBJECT
public:
    explicit Card(QString name,
                  QString description,
                  IncomeType incomeType,
                  CardType cardType,
                  ActionSource actionSource,
                  uchar price,
                  QSet<uchar> triggerRolls,
                  QObject *parent = nullptr);

    virtual ~Card();

    void virtual action(Player& activePlayer,
                        QVector<Player*>& otherPlayers);

    bool canTrigger(uchar currentRoll);

    QString description();

    QString name();

    uchar price();

signals:
    void applyAction(Player& activePlayer,
                     QVector<Player*>& otherPLayers,
                     ActionSource actionSource);

private:
    QString m_description;
    QString m_name;
    QSet<uchar> m_triggerRolls;
    int m_price;
    ActionSource m_actionSource;
    CardType m_cardType;
    IncomeType m_incomeType;
};

#endif // CARD_H

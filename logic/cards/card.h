#ifndef CARD_H
#define CARD_H

#include <QSet>
#include <memory>
#include <QString>

class Player;

enum class CardId : int
{
    RailwayStation      = 0,
    ShoppingMall        = 1,
    AmusementPark       = 2,
    RadioTower          = 3,
    WheatField          = 4,
    AnimalFarm          = 5,
    Bakery              = 6,
    Cafe                = 7,
    Shop                = 8,
    Forest              = 9,
    Stadium             = 10,
    TVCenter            = 11,
    BusinessCenter      = 12,
    CheeseFactory       = 13,
    FurnitureFactory    = 14,
    Mine                = 15,
    Restaurant          = 16,
    AppleOrchard        = 17,
    FruitMarket         = 18,
    None                = 19,
};

enum class CardType {
    Agricultural,
    Business,
    Dining,
    Farm,
    Fruit,
    Landmark,
    Mining,
    Production,
    Ship,
    Shop,
};

class Card {
public:
    Card(const QString& title,
         const QString& description,
         const QString& imagePath,
         const QSet<int> &activationValues,
         CardType type,
         int pack,
         int price,
         CardId id);

    virtual ~Card() = default;

    virtual void activate(QVector<std::shared_ptr<Player>>& players,
                          Player& owner,
                          Player& activePlayer,
                          int dice1,
                          int dice2) = 0;

    QSet<int> activationValues() const;

    QString description() const;

    CardId id() const;

    QString imagePath() const;

    bool hasActivationValue(int diceRoll) const;

    int pack() const;

    int price() const;

    QString title() const;

    CardType type() const;


protected:
    QString m_title;
    QString m_description;
    QString m_imagePath;
    QSet<int> m_activationValues;
    CardType m_type;
    int m_pack;
    int m_price;
    CardId m_id;
};

#endif // CARD_H

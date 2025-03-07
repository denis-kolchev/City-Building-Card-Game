#ifndef CARD_H
#define CARD_H

#include <QString>

class Player;

enum class CardType {
    Agricultiral,
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
    Card(const QString& name, const QString& description, CardType type, int activationValue);

    virtual ~Card() = default;

    virtual void activate(Player& owner, Player& activePlayer, int diceRoll) = 0;

    int activationValue() const;

    QString description() const;

    QString name() const;

    CardType type() const;


protected:
    QString m_name;
    QString m_description;
    CardType m_type;
    int m_activationValue;
};

#endif // CARD_H

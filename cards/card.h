#ifndef CARD_H
#define CARD_H

#include <QSet>
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
    Card(const QString& title,
         const QString& description,
         const QString& imagePath,
         const QSet<uchar> &activationValues,
         CardType type,
         uchar pack,
         uchar price);

    virtual ~Card() = default;

    virtual void activate(Player& owner, Player& activePlayer, int diceRoll) = 0;

    QSet<uchar> activationValues() const;

    QString description() const;

    QString imagePath() const;

    bool hasActivationValue(uchar diceRoll) const;

    uchar pack() const;

    uchar price() const;

    QString title() const;

    CardType type() const;


protected:
    QString m_title;
    QString m_description;
    QString m_imagePath;
    QSet<uchar> m_activationValues;
    CardType m_type;
    uchar m_pack;
    uchar m_price;
};

#endif // CARD_H

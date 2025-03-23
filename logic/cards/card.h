#ifndef CARD_H
#define CARD_H

#include <QSet>
#include <QString>

class Player;

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
         const QSet<uchar> &activationValues,
         CardType type,
         uchar pack,
         uchar price,
         uchar id);

    virtual ~Card() = default;

    virtual void activate(QVector<std::shared_ptr<Player>> players, Player& owner, Player& activePlayer, uchar dice1, uchar dice2) = 0;

    QSet<uchar> activationValues() const;

    QString description() const;

    uchar id() const;

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
    uchar m_id;
};

#endif // CARD_H

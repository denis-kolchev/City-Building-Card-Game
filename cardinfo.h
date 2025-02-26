#ifndef CARDINFO_H
#define CARDINFO_H

#include <QSet>
#include <QString>

enum class CardVariation {
    Start,
    Landmark,
    Build,
};

enum class IncomeType {
    None,
    Passive,
    Turn,
    Penalty,
    Tribute,
};

enum class CardType {
    None,
    Shop,
    Cafe, // Dining?
    Agricultiral,
    Landmark,
    Farm,
    Mining,
    Production,
    Fruit,
    Ship,
    Business
};

class CardInfo final
{
public:
    CardInfo() = delete;

    CardInfo(QString name, QString operation, CardVariation, IncomeType, CardType,
             int buildPrice, QSet<uchar> triggerRolls);

public:
    int buildPrice();

    bool canTrigger(uchar currentRoll);

    CardType cardType();

    CardVariation cardVariation();

    IncomeType incomeType();

    QString name();

    QString operation();

    QSet<uchar> triggerRolls();

private:
    QString m_name;
    QString m_operation;
    CardVariation m_cardVariation;
    IncomeType m_incomeType;
    CardType m_cardType;
    int m_buildPrice;
    QSet<uchar> m_triggerRolls;

};

#endif // CARDINFO_H

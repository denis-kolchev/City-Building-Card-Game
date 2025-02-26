#ifndef CARDINFO_H
#define CARDINFO_H

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
    Cafe,
    Agricultiral,
    Landmark,
};

class CardInfo
{
public:
    CardInfo() = delete;

    CardInfo(QString, QString, CardVariation, IncomeType, CardType,
             int, uchar, bool);

private:
    QString m_name;
    QString m_operation;
    CardVariation m_cardVariation;
    IncomeType m_incomeType;
    CardType m_cardType;
    int m_buildPrice;
    uchar m_triggerRoll;

};

#endif // CARDINFO_H

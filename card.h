#ifndef CARD_H
#define CARD_H

#include "abstractcard.h"

#include <QObject>

class Card : public QObject, public AbstractCard
{
    Q_OBJECT
public:
    explicit Card(CardInfo info, QObject *parent = nullptr);

    int buildPrice() override;

    IncomeType incomeType() override;

    void operate() override;

    CardVariation variation() override;

signals:

private:
    CardInfo m_info;
};

#endif // CARD_H

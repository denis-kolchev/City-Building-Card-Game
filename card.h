#ifndef CARD_H
#define CARD_H

#include "abstractcard.h"

#include <QObject>

class Card : public QObject, public AbstractCard
{
    Q_OBJECT
public:
    explicit Card(CardInfo info, QObject *parent = nullptr);

    uchar buildPrice() override;

    bool canTrigger(uchar currentRoll) override;

    IncomeType incomeType() override;

    QString name() override;

    void operate(GameState gameState) override;

    QString operation() override;

    QSet<uchar> virtual triggerRolls() override;

    CardVariation variation() override;

signals:

private:
    CardInfo m_info;
};

#endif // CARD_H

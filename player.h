#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

#include "card.h"

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(uchar m_id, QObject *parent = nullptr);

    bool canAfford(uchar cardPrice);

    QString name();

    void setName(QString name);

    uchar giveMoney(uchar numToGive);

    void applyPenalyIncome(Player& activePlayer);

    QVector<Card*> getCards(IncomeType type);

signals:

public slots:
    //void applyDiceEffect(uchar numDice);

    //void buyCard(Card* card);

private:
    QVector<Card*> m_cards;
    QString m_name;
    qsizetype m_money;
    uchar m_id;
    uchar curDiceResult = 0;
    bool isAI;
    bool hasTurn;
};

#endif // PLAYER_H

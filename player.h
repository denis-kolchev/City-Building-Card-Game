#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

#include "abstractcard.h"

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(uchar m_id, QObject *parent = nullptr);

    bool canAfford(uchar cardPrice);

    QString name();

    void setName(QString name);

signals:

public slots:
    void applyDiceEffect(uchar numDice);

    void buyCard(AbstractCard* card);


private:
    QVector<AbstractCard*> cards;
    QString m_name;
    qsizetype m_money;
    uchar m_id;
    uchar curDiceResult = 0;
    bool isAI;
    bool hasTurn;
};

#endif // PLAYER_H

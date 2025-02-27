#ifndef CARDRESERVE_H
#define CARDRESERVE_H

#include "card.h"

#include <QMap>
#include <QObject>

class Player;

class CardReserve : public QObject
{
    Q_OBJECT
public:
    explicit CardReserve(QObject *parent = nullptr);

signals:

private:
    QMap<Card*, uchar> m_builds;
    QSet<Card*> m_landmark;
};

#endif // CARDRESERVE_H

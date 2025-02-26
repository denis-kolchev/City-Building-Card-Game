#ifndef CARDRESERVE_H
#define CARDRESERVE_H

#include "abstractcard.h"

#include <QMap>
#include <QObject>

class CardReserve : public QObject
{
    Q_OBJECT
public:
    explicit CardReserve(QObject *parent = nullptr);

signals:

private:
    QMap<AbstractCard*, uchar> m_reserved;
};

#endif // CARDRESERVE_H

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

    QVector<Card*> getBuilds() {
        QVector <Card*> result;
        for (auto it = m_builds.begin(), ite = m_builds.end(); it != ite; ++it) {
            result.push_back(it.key());
        }
        return result;
    }

signals:
    void checkLandmarkEffect();

private:
    QMap<Card*, uchar> m_builds;
    QSet<Card*> m_landmark;
};

#endif // CARDRESERVE_H

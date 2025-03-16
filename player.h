#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <QMap>
#include <QObject>

#include "cards/card.h"

const int START_COINS_NUMBER = 3;

class Player : public QObject {
    Q_OBJECT

public:
    Player(const QString& name, QObject *parent = nullptr);

    void activateRollTwoDice();

    void activateOneMoreBuild();

    void addCard(std::shared_ptr<Card> card);

    void addCoins(int amount);

    void addLandmark(std::shared_ptr<Card> card);

    int coins() const;

    void deductMoney(int amount);

    QMap<std::shared_ptr<Card>, uchar> getCardsTable();

    QVector<std::shared_ptr<Card>> getLandmarks();

    uchar howManyCardsOfType(std::shared_ptr<Card> card);

    QString name() const;

    void triggerCards(QVector<std::shared_ptr<Player>> players, Player& activePlayer, uchar dice1, uchar dice2);

signals:
    void hasAmusementPark();

    void hasRailwayStation();

private:
    QMap<std::shared_ptr<Card>, uchar> m_cardsTable;
    QVector<std::shared_ptr<Card>> m_landmarks;
    QString m_name;
    int m_coins;
};


#endif // PLAYER_H

#ifndef INITIALPLAYERCARDSHANDLER_H
#define INITIALPLAYERCARDSHANDLER_H

#include "carddatahandler.h"

class InitialPlayerCardsHandler : public CardDataHandler {
public:
    explicit InitialPlayerCardsHandler(QVector<std::shared_ptr<Player>>& players);

    void handleCardData(QVector<std::shared_ptr<Card>> data) override;

private:
    QVector<std::shared_ptr<Player>>& m_players;
};

#endif // INITIALPLAYERCARDSHANDLER_H

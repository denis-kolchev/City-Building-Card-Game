#ifndef INITIALPLAYERCARDSHANDLER_H
#define INITIALPLAYERCARDSHANDLER_H

#include "carddatahandler.h"

class InitialPlayerCardsHandler : public CardDataHandler {
public:
    explicit InitialPlayerCardsHandler(std::shared_ptr<Player>& player);

    void handleCardData(QVector<std::shared_ptr<Card>> data) override;

private:
    std::shared_ptr<Player>& m_player;
};

#endif // INITIALPLAYERCARDSHANDLER_H

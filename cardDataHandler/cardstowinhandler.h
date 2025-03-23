#ifndef CARDSTOWINHANDLER_H
#define CARDSTOWINHANDLER_H

#include "carddatahandler.h"

class CardsToWinHandler : public CardDataHandler
{
public:
    explicit CardsToWinHandler(QVector<std::shared_ptr<Card>>& cardsToWin);

    void handleCardData(QVector<std::shared_ptr<Card>> data) override;

private:
    QVector<std::shared_ptr<Card>>& m_cardsToWin;
};

#endif // CARDSTOWINHANDLER_H

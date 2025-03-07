#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "cardreserve.h"
#include "cardwidget.h"

class GameController {
public:
    GameController(CardReserve& cardReserve, QObject* parent = nullptr);

    void createCardWidget(const QString& name, CardType type, int activationValue, const QPixmap& pixmap, const QColor& color);

    void onCardActivated(const QString& cardName, Player& owner, Player& activePlayer, int diceRoll);

private:
    CardReserve& m_cardReserve;

    QMap<QString, CardWidget*> m_cardWidgets;
};

#endif // GAMECONTROLLER_H

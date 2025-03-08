#include "gamecontroller.h"

GameController::GameController(CardReserve& cardReserve, QObject* parent)
    : m_cardReserve(cardReserve)
{
}

void GameController::createCardWidget(const QString& name,
                                      CardType type,
                                      int activationValue,
                                      const QPixmap& pixmap,
                                      const QColor& color)
{
    //m_cardWidgets.insert(name, new CardWidget(pixmap, QString::number(activationValue), "", "", "", "", color));


}

void GameController::onCardActivated(const QString& cardName, Player& owner, Player& activePlayer, int diceRoll)
{

}

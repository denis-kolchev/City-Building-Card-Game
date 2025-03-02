#include "gamelogic.h"

GameLogic::GameLogic(QObject *parent)
{
    for (uchar id = 0; id < 2; ++id) {
        m_players.push_back(new Player(id));
        m_players.push_back(new Player(id));
    }

    m_activePlayer = m_players[0];
    m_reserve = new CardReserve();

    for (auto& build : m_reserve->getBuilds()) {
        connect(build, CardReserve::checkLandmarkEffect, this, GameLogic::handleCardEffect());
    }
}

void GameLogic::endGame()
{
    /*
     * Game ends when it checks that all the landmarks are builded
     * That gamer wins
    */
}

void GameLogic::handleCardEffect(Player *m_activePlayer, Player* m_players)
{
    switch()
}

void GameLogic::processTurn()
{
    if (isGameFinished()) {
        emit endGame();
    }

    setNextPlayer();

    uchar diceResult = m_roller.rollDice(1); // from a button

    // Calculate penalty income for all players
    for (auto& player : m_players) {
        if (player != m_activePlayer) {
            auto penaltyCards = player->getCards(IncomeType::Penalty);
            uchar toGet = 0;
            for (auto& card : penaltyCards) {
                if (card->canTrigger(diceResult)) {
                    card->action(*m_activePlayer, m_players);
                }
            }
        }
    }


    // Sets new active player
    // active player do two states in one turn
    // 1. income state
    // 2. build state

    /*
     * INCOME STATE
     * 1. Dice the roll (1 or 2 depending on the condition)
     * 2. Check if some landmarks may influence to the cards effect
     * 3. Calculate penalty income for all players (except active one)
     * 4. Calculate passive income for all players (no exception)
     * 5. Calculate active income for active player
     * 6. Calculate tribute income for active player
     *
     * BUILD STATE
     * 1. Chose what to do (Build business, build landmark or skip)
     * 1.1 Build Business requre to pay to the bank. Card comes to player
     * 1.1.1 Check if some building contains a landmark sign, if so only 1 times build
     * 1.2 Build a landmark pays the money to back and it makes it active
     * 1.3 Doing nothing means check some cards which require not to build something
    */

    /*
        type amount of some card close to it
        change type of landmark to a signle building?
    */
}

void GameLogic::updateGameState()
{

}

void GameLogic::applyDiceResult(int result, Player *player)
{

}

void GameLogic::performPlayerAction(ActionType, Player *player)
{

}

void GameLogic::setNextPlayer()
{

}

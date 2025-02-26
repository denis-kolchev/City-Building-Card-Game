#include "gamestate.h"

GameState::GameState(QVector<Player*>& players,
                     Player& currentPlayer,
                     CardReserve& reserve)
    : m_players(players), m_currentPlayer(currentPlayer), m_reserve(reserve)

{
}

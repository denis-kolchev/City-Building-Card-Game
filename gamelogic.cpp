#include "gamelogic.h"

GameLogic::GameLogic(const QVector<QString>& playerNames) : m_currentPlayerId(0) {
    for (const auto& name : playerNames) {
        m_players.emplace_back(name);
    }
}

Player&GameLogic::getPlayer(int id) {
    return m_players[id];
}

void GameLogic::playTurn() {
    Player& activePlayer = m_players[m_currentPlayerId];
    int diceRoll = m_roller.rollDice(1);

    qDebug() << activePlayer.name() << " rolled a " << diceRoll << ".\n";

    // Trigger cards for all players
    for (auto& player : m_players) {
        player.triggerCards(diceRoll, activePlayer);
    }

    // Move to the next player
    m_currentPlayerId = (m_currentPlayerId + 1) % m_players.size();
}

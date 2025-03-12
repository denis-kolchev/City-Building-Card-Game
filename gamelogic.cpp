#include "gamelogic.h"

#include <QCoreApplication>
#include <QDir>

GameLogic::GameLogic(QObject *parent)
    : m_currentPlayerId(0), QObject(parent)
{
    // find a way to config file
    QString executablePath = QCoreApplication::applicationDirPath();
    QDir sourceDir(executablePath);
    sourceDir.cd("../../../"); // Move on 3 levels up
    QString configPath = sourceDir.absolutePath() + "/CardsDataConfig.ini";
    if (QFile::exists(configPath)) {
        qDebug() << "Config file has found: " << configPath;
    } else {
        qDebug() << "File not found!";
    }

    // read card data from config
    CardDataConfigReader cardReader(configPath);
    m_cardsToWin = cardReader.readFromRange(0, 3);
}

GameLogic::~GameLogic()
{
}

int GameLogic::currentPlayerId() const {
    return m_currentPlayerId;
}

bool GameLogic::isGameIsFinished() {
    for (auto& player : m_players) {
        auto cardsTable = player.getCardsTable();
        int count = 0;
        for (auto& card : m_cardsToWin) {
            if (cardsTable.find(card) != cardsTable.end()) {
                count++;
            }
        }

        if (count == cardsTable.size()) {
            return true;
        }
    }
    return false;
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
    emit currentPlayerChanged(m_currentPlayerId);
}

void GameLogic::handleCreatePlayers(QList<QString> playerNames)
{
    for (int i = 0; i < playerNames.size(); ++i) {
        m_players.push_back(Player(playerNames.at(i)));
    }
}


void GameLogic::handleRollButtonClicked(uchar diceRoll)
{
    playTurn();
    //emit waitForBuyOrSkip();
}

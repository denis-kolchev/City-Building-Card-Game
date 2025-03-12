#include "gamelogic.h"
#include "carddataconfigreader.h"

#include <QCoreApplication>
#include <QDir>

GameLogic::GameLogic(QObject *parent)
    : m_cardReserve(new CardReserve()), m_currentPlayerId(0), QObject(parent)
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
    // Active player loss money, get money from other players
    for (auto& player : m_players) {
        player.triggerCards(diceRoll, activePlayer);
    }

    // Now, build time!
    emit incomeStageFinished();
    return;
}

void GameLogic::checkCoinBalanceForCard(QString cardTitle)
{
    uchar coins = m_players[m_currentPlayerId].coins();
    emit tryToBuyCard(cardTitle, coins);
}

void GameLogic::giveCardToPlayer(std::shared_ptr<Card> card)
{
    m_players[m_currentPlayerId].deductMoney(card->price());
    m_players[m_currentPlayerId].addCard(card);

    // Move to the next player
    m_currentPlayerId = (m_currentPlayerId + 1) % m_players.size();
    emit playerBuildNewBuilding(card);
    emit buildStageFinished(m_currentPlayerId);
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

void GameLogic::handleTryToBuyCard(QString cardTitle)
{
    auto card = m_cardReserve->findCardByTitle(cardTitle);
    if (!card) {
        // need an emit somewhere to rewdraw reserve without a card
        return; // no more cards of this type!
    }

    uchar cardPrice = card->price();
    uchar playerBalance = m_players[m_currentPlayerId].coins();
    if (cardPrice <= playerBalance) {
        m_players[m_currentPlayerId].deductMoney(cardPrice);
        m_players[m_currentPlayerId].addCard(card);
        m_cardReserve->removeCard(card);
        emit playerBuildNewBuilding(card);
    } else {
        // Maybe it should be displayed as a worning somewhere
        qDebug() << "Card is Too expensive!";
    }
}

void GameLogic::prepateNextTurn()
{
    // Move to the next player
    m_currentPlayerId = (m_currentPlayerId + 1) % m_players.size();
    buildStageFinished(m_currentPlayerId);
}

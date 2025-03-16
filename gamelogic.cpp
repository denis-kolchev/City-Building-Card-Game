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
    m_cardReader = new CardDataConfigReader(configPath);
    m_cardsToWin = m_cardReader->readFromRange(0, 3);
}

GameLogic::~GameLogic()
{
}

int GameLogic::currentPlayerId() const {
    return m_currentPlayerId;
}

bool GameLogic::isGameIsFinished() {
    int mx = 0;
    for (auto player : m_players) {
        mx = fmax(mx, player->getLandmarks().size());
        if (player->getLandmarks().size() == m_cardsToWin.size()) {
            return true;
        }
    }
    qDebug() << "------> The most number of landmarks is: " << mx;
    return false;
}

std::shared_ptr<Player> GameLogic::getPlayer(int id) {
    return m_players[id];
}

void GameLogic::playTurn(uchar diceRoll) {
    auto activePlayer = m_players[m_currentPlayerId];

    qDebug() << activePlayer->name() << " rolled a " << diceRoll << ".\n";

    // Trigger cards for all players
    // Active player loss money, get money from other players
    int i = 0;
    for (auto& player : m_players) {
        player->triggerCards(m_players, *activePlayer, diceRoll);
        // Now, build time!
        emit playerBalanceChanged(player->coins(), i++);
    }
}

void GameLogic::checkCoinBalanceForCard(QString cardTitle)
{
    uchar coins = m_players[m_currentPlayerId]->coins();
    emit tryToBuyCard(cardTitle, coins);
}

void GameLogic::giveCardToPlayer(std::shared_ptr<Card> card)
{
    m_players[m_currentPlayerId]->deductMoney(card->price());
    m_players[m_currentPlayerId]->addCard(card);

    // Move to the next player
    m_currentPlayerId = (m_currentPlayerId + 1) % m_players.size();
    emit playerBuildNewBuilding(card);
    emit buildStageFinished(m_currentPlayerId);
}

void GameLogic::handleCreatePlayers(QList<QString> playerNames)
{
    for (int i = 0; i < playerNames.size(); ++i) {
        auto player = std::make_shared<Player>(playerNames.at(i));
        connect(player.get(), &Player::hasRailwayStation, this, &GameLogic::handlePlayerHasRailwayStation);
        player->addCard(m_cardReader->readFromRange(4, 4).at(0));
        player->addCard(m_cardReader->readFromRange(6, 6).at(0));
        m_players.push_back(player);
    }
}

void GameLogic::handlePlayerHasRailwayStation()
{
    emit playerHasRailwayStation();
}

void GameLogic::handleRollButtonClicked(uchar diceRoll)
{
    playTurn(diceRoll);
    //emit waitForBuyOrSkip();
}

void GameLogic::handleTryToBuyCard(QString cardTitle)
{
    auto card = m_cardReserve->findCardByTitle(cardTitle);
    if (!card) {
        qDebug() << "Card isn't found!";
        // need an emit somewhere to rewdraw reserve without a card
        return; // no more cards of this type!
    }

    uchar cardPrice = card->price();
    uchar playerBalance = m_players[m_currentPlayerId]->coins();
    if (cardPrice <= playerBalance) {
        m_players[m_currentPlayerId]->deductMoney(cardPrice);
        emit playerBalanceChanged(m_players[m_currentPlayerId]->coins(), m_currentPlayerId);

        if (!card->hasActivationValue(0)) { // player buying from Reserve
            m_players[m_currentPlayerId]->addCard(card);
            m_cardReserve->removeCard(card);
            emit playerBuildNewBuilding(card);
        } else { // player buing Landmark
            m_players[m_currentPlayerId]->addLandmark(card);
            m_cardReserve->removeLandmark(card);
            emit playerBuildLandmark(card);
        }

    } else {
        // Maybe it should be displayed as a worning somewhere
        qDebug() << "Card is Too expensive!";
    }
}

void GameLogic::moveToNextPlaer()
{
    // Move to the next player
    m_currentPlayerId = (m_currentPlayerId + 1) % m_players.size();
    emit buildStageFinished(m_currentPlayerId);
}

void GameLogic::prepateNextTurn()
{
    if (isGameIsFinished()) {
        qDebug() << "Game isfinished";
        emit gameIsFinished(m_currentPlayerId);
    }

    // Move to the next player
    m_currentPlayerId = (m_currentPlayerId + 1) % m_players.size();
    buildStageFinished(m_currentPlayerId);
}

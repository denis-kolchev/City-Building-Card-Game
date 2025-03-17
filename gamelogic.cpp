#include "gamelogic.h"
#include "carddataconfigreader.h"

#include <QCoreApplication>
#include <QDir>

GameLogic::GameLogic(QObject *parent)
    : m_cardReserve(new CardReserve()), m_currentPlayerId(0), QObject(parent)
{
    QString configPath = QCoreApplication::applicationDirPath() + "/CardsDataConfig.ini";
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

void GameLogic::playTurn(uchar dice1, uchar dice2) {
    auto activePlayer = m_players[m_currentPlayerId];

    if (dice2 == 0) {
        qDebug() << activePlayer->name() << " rolled a " << dice1 << ".\n";
    } else {
        qDebug() << activePlayer->name() << " rolled a " << dice1 << " & " << dice2 << ".\n";
    }

    // Trigger cards for all players
    // Active player loss money, get money from other players
    int i = 0;
    for (auto& player : m_players) {
        player->triggerCards(m_players, *activePlayer, dice1, dice2);
        // Now, build time!
        emit playerBalanceChanged(player->coins(), i++);
    }
}

void GameLogic::checkCoinBalanceForCard(uchar cardId)
{
    uchar coins = m_players[m_currentPlayerId]->coins();
    emit tryToBuyCard(cardId, coins);
}

void GameLogic::processCheckPlayerCards(uchar cardId, int playerId, uchar dice1, uchar dice2)
{
    auto cards = m_players[m_currentPlayerId]->getLandmarks(); // ToDO UNITE THESE TWO FUNCTIONS!
    for (auto card : cards) {
        if (card->id() == cardId) {
            card->activate(m_players, *m_players[m_currentPlayerId], *m_players[m_currentPlayerId], dice1, dice1);
        }
    }
    emit playerCardActivatedBefore(dice1, dice2);
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
        connect(player.get(), &Player::hasAmusementPark, this, &GameLogic::handlePlayerHasAmusementPark);
        connect(player.get(), &Player::hasRadioTower, this, &GameLogic::handlePlayerHasRadioTower);
        player->addCard(m_cardReader->readFromRange(4, 4).at(0));
        player->addCard(m_cardReader->readFromRange(6, 6).at(0));
        m_players.push_back(player);
    }
}

void GameLogic::handlePlayerHasAmusementPark()
{
    emit playerHasAmusementPark();
}

void GameLogic::handlePlayerHasRadioTower()
{
    emit playerHasRadioTower();
}

void GameLogic::handlePlayerHasRailwayStation()
{
    emit playerHasRailwayStation();
}

void GameLogic::handleRollButtonClicked(uchar dice1, uchar dice2)
{
    playTurn(dice1, dice2);
    //emit waitForBuyOrSkip();
}

void GameLogic::handleTryToBuyCard(uchar cardId)
{
    auto card = m_cardReserve->findCardByTitle(cardId);
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

        if (card->hasActivationValue(0)) { // player builds Landmark
            m_players[m_currentPlayerId]->addLandmark(card);
            m_cardReserve->removeLandmark(card);
            emit playerBuildLandmark(card);
        } else {// player builds from Reserve
            m_players[m_currentPlayerId]->addCard(card);
            m_cardReserve->removeCard(card);
            emit playerBuildNewBuilding(card);
        }

    } else {
        emit playerHasNotEnoughCoins("You have not enough coins to buy it.");
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

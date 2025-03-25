#include "gamelogic.h"
#include "../cardDataHandler/bankcardshandler.h"
#include "../cardDataHandler/initialplayercardshandler.h"
#include "../carddataconfigreader.h"

#include <QCoreApplication>
#include <QDir>

GameLogic::GameLogic(QObject *parent)
    : m_bank(new Bank()), m_currentPlayerId(0), QObject(parent)
{
    connect(m_bank.get(), &Bank::bankGetsCard, this, [this](std::shared_ptr<Card> card) {
        emit bankGetsCard(card);
    });
    connect(m_bank.get(), &Bank::bankLoosesCard, this, [this](std::shared_ptr<Card> card) {
        emit bankLoosesCard(card);
    });
}

GameLogic::~GameLogic()
{
}

int GameLogic::currentPlayerId() const
{
    return m_currentPlayerId;
}

bool GameLogic::isGameIsFinished()
{
    int mx = 0;
    for (auto player : m_players) {
        mx = fmax(mx, player->getLandmarks().size());
        if (player->getLandmarks().size() == m_cardsToWin.size()) {
            return true;
        }
    }
    return false;
}

std::shared_ptr<Player> GameLogic::getPlayer(int id)
{
    return m_players[id];
}

void GameLogic::playTurn(uchar dice1, uchar dice2)
{
    for (const auto& player : std::as_const(m_players)) {
        if (player != nullptr) {
            player->triggerCards(m_players, *m_players[m_currentPlayerId], dice1, dice2);
        }
        // if (player == nullptr) {
        //     qDebug() << "player is nullptr 1!";
        // }
        // qDebug() << "--- old " << player->name() << " balance:" << player->coins();
        // if (player == nullptr) {
        //     qDebug() << "player is nullptr 2!";
        // }
        // player->triggerCards(m_players, *m_players[m_currentPlayerId], dice1, dice2);
        // if (player == nullptr) {
        //     // Why it's nullptr here?
        //     qDebug() << "player is nullptr 3!";
        // }
        // qDebug() << "--- new " << player->name() << " balance:" << player->coins();
        // if (player == nullptr) {
        //     qDebug() << "player is nullptr 4!";
        // }
    }
}

void GameLogic::checkCoinBalanceForCard(uchar cardId)
{
    uchar coins = m_players[m_currentPlayerId]->coins();
    emit tryToBuyCard(cardId, coins);
}

void GameLogic::processCheckPlayerCards(uchar cardId, int playerId, uchar dice1, uchar dice2)
{
    auto cards = m_players[m_currentPlayerId]->getLandmarks();
    for (auto it = cards.begin(), ite = cards.end(); it != ite; ++it) {
        if (it.key()->id() == cardId) {
            it.key()->activate(m_players, *m_players[m_currentPlayerId], *m_players[m_currentPlayerId], dice1, dice1);
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

void GameLogic::handleCardDataReceived(QVector<std::shared_ptr<Card>> data)
{
    m_cardsToWin = data;
    qDebug() << "Card data received and processed.";
}

void GameLogic::handleConfigDataReady()
{
    // usufull to check if some player won the game.
    // TODO Seems like it should be just id-s, not real cards
    //emit requestCardData(0, 3, std::make_shared<CardsToWinHandler>(m_cardsToWin));

    // request cards to fill in the bank (so players could buy them)
    // every std::shared_ptr<CardInventory> somehow should know cardScrollWidget
    // to which they should place their cards
    const int mxBaseCards = 6;
    for (int i = 0; i < mxBaseCards; ++i) {
        emit requestCardData(4, 9, std::make_shared<BankCardsHandler>(m_bank));
        emit requestCardData(13, 18, std::make_shared<BankCardsHandler>(m_bank));
    }
}

void GameLogic::handleCreatePlayers(QList<QString> playerNames)
{
    for (int id = 0; id < playerNames.size(); ++id) {
        auto player = std::make_shared<Player>(playerNames.at(id), id);
        connect(player.get(), &Player::hasRailwayStation, this, &GameLogic::handlePlayerHasRailwayStation);
        connect(player.get(), &Player::hasAmusementPark, this, &GameLogic::handlePlayerHasAmusementPark);
        connect(player.get(), &Player::hasRadioTower, this, &GameLogic::handlePlayerHasRadioTower);
        connect(player.get(), &Player::playerBalanceChanged, this, [this, player]() {
            emit playerBalanceChanged(player->coins(), player->id());
        });
        connect(player.get(), &Player::playerGetsCard, this, [this](int playerId, std::shared_ptr<Card> card) {
            emit playerGetsCard(playerId, card);
        });
        connect(player.get(), &Player::playerLoosesCard, this, [this](int playerId, std::shared_ptr<Card> card) {
            emit playerLoosesCard(playerId, card);
        });

        emit requestCardData(0, 3, std::make_shared<BankCardsHandler>(m_bank));
        emit requestCardData(10, 12, std::make_shared<BankCardsHandler>(m_bank));
        emit requestCardData(4, 4, std::make_shared<InitialPlayerCardsHandler>(player)); // give to player a card with id 4
        emit requestCardData(6, 6, std::make_shared<InitialPlayerCardsHandler>(player)); // give to player a card with id 6
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
}

void GameLogic::handleTryToBuyCard(uchar cardId)
{
    auto card = m_bank->findCardById(cardId);
    if (!card) {
        qDebug() << "Card isn't found!";
        return; // no more cards of this type!
    }

    uchar cardPrice = card->price();
    uchar playerBalance = m_players[m_currentPlayerId]->coins();
    if (cardPrice <= playerBalance) {
        m_players[m_currentPlayerId]->deductMoney(cardPrice);

        if (card->hasActivationValue(0)) { // player builds Landmark
            m_players[m_currentPlayerId]->addCard(card);
            m_bank->removeCard(card);
            emit playerBuildLandmark(card);
        } else {
            m_players[m_currentPlayerId]->addCard(card);
            m_bank->removeCard(card);
            emit playerBuildNewBuilding(card);
        }

    } else {
        emit playerHasNotEnoughCoins("You have not enough coins to buy it.");
    }
}

void GameLogic::moveToNextPlaer()
{
    m_currentPlayerId = (m_currentPlayerId + 1) % m_players.size();
    emit buildStageFinished(m_currentPlayerId);
}

void GameLogic::prepateNextTurn()
{
    if (isGameIsFinished()) {
        qDebug() << "Game isfinished";
        emit gameIsFinished(m_currentPlayerId);
    }

    moveToNextPlaer();
}

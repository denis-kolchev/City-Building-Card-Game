#include "gamelogic.h"
#include "../carddataconfigreader.h"
#include "bankcardshandler.h"
#include "initialplayercardshandler.h"

#include <QCoreApplication>
#include <QDir>
#include <QMetaMethod>
#include <QTimer>

GameLogic::GameLogic(QObject *parent)
    : m_bank(std::make_shared<Bank>())
    , m_cardToWinIds{ CardId::RailwayStation,
                     CardId::ShoppingMall,
                     CardId::AmusementPark,
                     CardId::RadioTower }
    , m_currentPlayerId(0)
    , QObject(parent)
{
    // banks as part of game logic sends signals to UI
    connect(m_bank.get(), &Bank::bankGetsCard, this, &GameLogic::sendBankGetsCard);
    connect(m_bank.get(), &Bank::bankLoosesCard, this, &GameLogic::sendBankLoosesCard);
}

GameLogic::~GameLogic()
{
}

void GameLogic::handleCardClickedForPurchase(CardId cardId)
{
    auto currentPlayer = m_players[m_currentPlayerId];
    auto cardData = m_bank->findCardById(cardId);

    if (!cardData) {
        return;
    }

    if (cardData->activationValues().contains(0) || cardData->type() == CardType::Landmark) {
        // player clicked on purple card or on landmakr which might be purchased only once (game rules)
        if (currentPlayer->findCardById(cardId)) {
            emit sendCardPurchaseFailed(m_currentPlayerId, cardId, tr("You can purchase this card only once."));
            return;
        }
    }

    if (cardData->price() > currentPlayer->balance()) {
        emit sendCardPurchaseFailed(m_currentPlayerId, cardId, tr("This card is too expensive."));
        return;
    }

    // if player has AmusementPark, they can purchase cards twice (game rules)
    if (currentPlayer->hasCard(CardId::AmusementPark) && currentPlayer->canPurchaseTwice()) {
        currentPlayer->setCanPurchaseTwice(false);
        purchaseCard(cardData);
        return;
    }

    purchaseCard(cardData);
    emit finishPurchaseState(m_currentPlayerId);
    resetPlayerTurnState();
}

void GameLogic::handleConfigDataReadyToRead()
{
    const int mxBaseCards = 6;
    for (int i = 0; i < mxBaseCards; ++i) {
        emit requestCardData(CardId::WheatField, CardId::Forest, std::make_shared<BankCardsHandler>(m_bank));
        emit requestCardData(CardId::CheeseFactory, CardId::FruitMarket, std::make_shared<BankCardsHandler>(m_bank));
    }
}

void GameLogic::handleCreatePlayers(int playerCount)
{
    for (int playerId = 0; playerId < playerCount; ++playerId) {
        auto player = std::make_shared<Player>(
            QString("Player %1").arg(char(playerId + 'A')),
            playerId
        );

        connect(player.get(), &Player::playerGetsCard, this, &GameLogic::sendPlayerGetsCard);
        connect(player.get(), &Player::playerLoosesCard, this, &GameLogic::sendPlayerLoosesCard);
        connect(player.get(), &Player::playerBalanceChanged, this, &GameLogic::sendPlayerBalanceChanged);

        // Purple cards are available to buy only once for each player (game rules)
        // Landmarks are available to buy only once for each player (game rules)
        emit requestCardData(CardId::Stadium, CardId::BusinessCenter, std::make_shared<BankCardsHandler>(m_bank));
        emit requestCardData(CardId::RailwayStation, CardId::RadioTower, std::make_shared<BankCardsHandler>(m_bank));

        // When the game starts each players gets card starter pack - wheat field & bakery (game rules)
        emit requestCardData(CardId::WheatField, CardId::WheatField, std::make_shared<InitialPlayerCardsHandler>(player));
        emit requestCardData(CardId::Bakery, CardId::Bakery, std::make_shared<InitialPlayerCardsHandler>(player));

        m_players.push_back(player);
    }
}

void GameLogic::handleRollDiceButtonClicked(int diceRollCount)
{
    rollDice(diceRollCount);
}

void GameLogic::handleSkipButtonClicked()
{
    auto currentPlayer = m_players[m_currentPlayerId];
    // if player has AmusementPark, they can purchase cards twice (game rules)
    if (currentPlayer->hasCard(CardId::AmusementPark) && currentPlayer->canPurchaseTwice()) {
        currentPlayer->setCanPurchaseTwice(false);
        return;
    }

    emit finishPurchaseState(m_currentPlayerId);
    resetPlayerTurnState();
}

void GameLogic::receiveDiceRerollResponse(QVector<int> rollResults, bool confirmed)
{
    if (!confirmed) {
        activatePlayersCards(rollResults);
    }

    // if confirmed
    // wait from player to click roll 1 dice or roll 2 dice buttons again
}

void GameLogic::activatePlayersCards(QVector<int> rollResults)
{
    for (const auto& player : std::as_const(m_players)) {
        if (player != nullptr) {
            player->activateCards(m_players, m_players[m_currentPlayerId], rollResults[0], rollResults[1]);
        }
    }

    emit finishIncomeState(m_currentPlayerId);
}

void GameLogic::checkWinCondition()
{
    auto currentPlayer = m_players[m_currentPlayerId];
    auto landmarkCount = std::count_if(m_cardToWinIds.begin(), m_cardToWinIds.end(), [&currentPlayer](auto cardId) {
        return currentPlayer->findCardById(cardId) != nullptr;
    });

    if (m_cardToWinIds.size() == landmarkCount) {
        emit gameWon(m_currentPlayerId);
    }
}

void GameLogic::purchaseCard(std::shared_ptr<Card> card)
{
    m_players[m_currentPlayerId]->deductMoney(card->price());
    m_players[m_currentPlayerId]->addCard(card);
    m_bank->removeCard(card);

    checkWinCondition();
}

void GameLogic::resetPlayerTurnState()
{
    emit finishPurchaseState(m_currentPlayerId);
    m_currentPlayerId = (m_currentPlayerId + 1) % m_players.size();

    setupCurrentPlayerSpecialAbilities();

    if (m_players[m_currentPlayerId]->hasCard(CardId::RailwayStation) && m_players[m_currentPlayerId]->canRollTwoDice()) {
        m_players[m_currentPlayerId]->setCanRollTwoDice(false);
        emit sendRollTwoDiceAvailable(m_currentPlayerId);
    }

    emit finishWaitState(m_currentPlayerId);
}

void GameLogic::rollDice(int diceRollCount)
{
    const int maxRollNumber = 2;
    const int diceRollPerTryCount = 1;
    QVector<int> rollResults(maxRollNumber, 0);
    for (int i = 0; i < diceRollCount; ++i) {
        rollResults[i] = DiceRoller{}.rollDice(diceRollPerTryCount);
    }

    emit sendDiceRollResult(m_currentPlayerId, rollResults);

    auto currentPlayer = m_players[m_currentPlayerId];
    // if player has RadioTower, they can reroll the dice once (game rules)
    if (currentPlayer->hasCard(CardId::RadioTower) && currentPlayer->canRerollDice()) {
        currentPlayer->setCanRerollDice(false);
        emit requestDiceRerollConfirmation(currentPlayer->id(), rollResults);
        return;
    }

    QTimer::singleShot(200, this, [this]() {  // 100ms delay
        emit finishIncomeState(m_currentPlayerId);
    });

    activatePlayersCards(rollResults);
}

void GameLogic::setupCurrentPlayerSpecialAbilities()
{
    // getting back all spent card abilities to use them again (game rules)
    auto currentPlayer = m_players[m_currentPlayerId];
    if (currentPlayer->hasCard(CardId::RadioTower)) {
        currentPlayer->setCanRerollDice(true);
    }
    if (currentPlayer->hasCard(CardId::AmusementPark)) {
        currentPlayer->setCanPurchaseTwice(true);
    }
    if (currentPlayer->hasCard(CardId::RailwayStation)) {
        currentPlayer->setCanRollTwoDice(true);
    }
}

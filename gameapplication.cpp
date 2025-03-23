#include "gameapplication.h"

GameApplication::GameApplication(std::shared_ptr<CardDataConfigReader> configReader,
                                 std::shared_ptr<GameLogic> logic,
                                 std::shared_ptr<MainWindow> window,
                                 std::shared_ptr<StartMenu> menu)
    : m_configReader(configReader)
    , m_gameLogic(logic)
    , m_mainWindow(window)
    , m_startMenu(menu)
{
    setupConnections();
}

void GameApplication::run()
{
    m_startMenu->show();
}

void GameApplication::setupConnections()
{
    QObject::connect(m_gameLogic->bank().get(), &CardInventory::cardAdded,
                     m_mainWindow->getBankScrollWidget(), &CardScrollWidget::addCard);

    QObject::connect(m_gameLogic->bank().get(), &CardInventory::cardRemoved,
                     m_mainWindow->getBankScrollWidget(), &CardScrollWidget::removeCard);

    QObject::connect(m_configReader.get(), &CardDataConfigReader::configDataReady,
                     m_gameLogic.get(), &GameLogic::handleConfigDataReady);

    QObject::connect(m_gameLogic.get(), &GameLogic::requestReadFromRange,
                     m_configReader.get(), &CardDataConfigReader::handleReadFromRange);

    QObject::connect(m_configReader.get(), &CardDataConfigReader::sendCardData,
                     m_gameLogic.get(), &GameLogic::handleCardDataReceived);

    QObject::connect(m_gameLogic.get(), &GameLogic::requestCardData,
                     m_configReader.get(), &CardDataConfigReader::requestCardData);

    QObject::connect(m_startMenu.get(), &StartMenu::showMainWindow,
                     m_mainWindow.get(), &MainWindow::handleShowMainWindow);

    QObject::connect(m_mainWindow.get(), &MainWindow::createPlayers,
                     m_gameLogic.get(), &GameLogic::handleCreatePlayers);

    QObject::connect(m_mainWindow.get(), &MainWindow::diceRollAccepted,
                     m_gameLogic.get(), &GameLogic::handleRollButtonClicked);

    QObject::connect(m_mainWindow.get(), &MainWindow::checkPlayerCards,
                     m_gameLogic.get(), &GameLogic::processCheckPlayerCards);

    QObject::connect(m_gameLogic.get(), &GameLogic::playerCardActivatedBefore,
                     m_mainWindow.get(), &MainWindow::handlePlayerCardActivatedBefore);

    QObject::connect(m_gameLogic.get(), &GameLogic::buildStageFinished,
                     m_mainWindow.get(), &MainWindow::repaintPlayerPanel);

    QObject::connect(m_mainWindow.get(), &MainWindow::cardWidgetClicked,
                     m_gameLogic.get(), &GameLogic::handleTryToBuyCard);

    QObject::connect(m_gameLogic.get(), &GameLogic::playerBuildNewBuilding,
                     m_mainWindow.get(), &MainWindow::displayPlayerNewCard);

    QObject::connect(m_mainWindow.get(), &MainWindow::updatedPlayersPanel,
                     m_gameLogic.get(), &GameLogic::prepateNextTurn);

    QObject::connect(m_gameLogic.get(), &GameLogic::playerBalanceChanged,
                     m_mainWindow.get(), &MainWindow::updatePlayerBalanceLabel);

    QObject::connect(m_mainWindow.get(), &MainWindow::skipClicked,
                     m_gameLogic.get(), &GameLogic::moveToNextPlaer);

    QObject::connect(m_gameLogic.get(), &GameLogic::playerHasRailwayStation,
                     m_mainWindow.get(), &MainWindow::unlockRollTwoDiceButton);

    QObject::connect(m_gameLogic.get(), &GameLogic::playerHasAmusementPark,
                     m_mainWindow.get(), &MainWindow::unlockBuildAgainIfDubleRollDice);

    QObject::connect(m_gameLogic.get(), &GameLogic::playerHasRadioTower,
                     m_mainWindow.get(), &MainWindow::unlockDiceReroll);

    QObject::connect(m_gameLogic.get(), &GameLogic::playerBuildLandmark,
                     m_mainWindow.get(), &MainWindow::unlockPlayerLandmark);

    QObject::connect(m_gameLogic.get(), &GameLogic::gameIsFinished,
                     m_mainWindow.get(), &MainWindow::finishGame);

    QObject::connect(m_gameLogic.get(), &GameLogic::playerHasNotEnoughCoins,
                     m_mainWindow.get(), &MainWindow::displayWorningWindow);

}

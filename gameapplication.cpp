#include "gameapplication.h"

GameApplication::GameApplication(std::shared_ptr<CardDataConfigReader> configReader,
                                 std::shared_ptr<GameLogic> logic,
                                 std::shared_ptr<MainWindow> window,
                                 std::shared_ptr<NetworkManager> network,
                                 std::shared_ptr<StartMenu> menu)
    : m_configReader(configReader)
    , m_gameLogic(logic)
    , m_mainWindow(window)
    , m_network(network)
    , m_startMenu(menu)
{
    setupConnections();
}

void GameApplication::run()
{
    if (m_configReader->isConfigDataReady()) {
        emit m_configReader->configDataReadyToRead();
    }

    m_startMenu->show();
}

void GameApplication::setupConnections()
{
    // startMenu -> NetworkManager
    QObject::connect(m_startMenu.get(), &StartMenu::onCreateServer,
                     m_network.get(), &NetworkManager::createServer);

    QObject::connect(m_startMenu.get(), &StartMenu::onCreateClient,
                     m_network.get(), &NetworkManager::createClient);

    // NetworkManager -> startMenu
    QObject::connect(m_network.get(), &NetworkManager::notifyPlayerWithMessageBox,
                     m_startMenu.get(), &StartMenu::showMessage);

    // NetworkManager -> startMenu
    QObject::connect(m_network.get(), &NetworkManager::networkGameInit,
                     m_startMenu.get(), &StartMenu::showMainWindow);

    // NetworkManager -> mainWindow
    QObject::connect(m_network.get(), &NetworkManager::networkDiceRollResult,
                     m_mainWindow.get(), &MainWindow::receiveDiceRollResult);

    QObject::connect(m_network.get(), &NetworkManager::networkFinishIncomeState,
                     m_mainWindow.get(), &MainWindow::handleFinishIncomeState);

    // startMenu -> mainWindow
    QObject::connect(m_startMenu.get(), &StartMenu::showMainWindow,
                     m_mainWindow.get(), &MainWindow::handleShowMainWindow);

    // configReader -> gameLogic
    QObject::connect(m_configReader.get(), &CardDataConfigReader::configDataReadyToRead,
                     m_gameLogic.get(), &GameLogic::handleConfigDataReadyToRead);

    // gameLogic -> configReader
    QObject::connect(m_gameLogic.get(), &GameLogic::requestCardData,
                     m_configReader.get(), &CardDataConfigReader::handleRequestCardData);

    // gameLogic -> mainWindow
    QObject::connect(m_gameLogic.get(), &GameLogic::gameWon,
                     m_mainWindow.get(), &MainWindow::handleGameWon);

    QObject::connect(m_gameLogic.get(), &GameLogic::requestDiceRerollConfirmation,
                     m_mainWindow.get(), &MainWindow::handleRequestDiceRerollConfirmation);

    QObject::connect(m_gameLogic.get(), &GameLogic::sendBankGetsCard,
                     m_mainWindow.get(), &MainWindow::receiveBankGetsCard);

    QObject::connect(m_gameLogic.get(), &GameLogic::sendBankLoosesCard,
                     m_mainWindow.get(), &MainWindow::receiveBankLoosesCard);

    QObject::connect(m_gameLogic.get(), &GameLogic::sendCardPurchaseFailed,
                     m_mainWindow.get(), &MainWindow::receiveCardPurchaseFailed);

    QObject::connect(m_gameLogic.get(), &GameLogic::sendDiceRollResult,
                     m_mainWindow.get(), &MainWindow::receiveDiceRollResult);

    QObject::connect(m_gameLogic.get(), &GameLogic::sendPlayerBalanceChanged,
                     m_mainWindow.get(), &MainWindow::receivePlayerBalanceChanged);

    QObject::connect(m_gameLogic.get(), &GameLogic::sendPlayerGetsCard,
                     m_mainWindow.get(), &MainWindow::receivePlayerGetsCard);

    QObject::connect(m_gameLogic.get(), &GameLogic::sendPlayerLoosesCard,
                     m_mainWindow.get(), &MainWindow::receivePlayerLoosesCard);

    QObject::connect(m_gameLogic.get(), &GameLogic::sendRollTwoDiceAvailable,
                     m_mainWindow.get(), &MainWindow::receiveRollTwoDiceAvailable);

    QObject::connect(m_gameLogic.get(), &GameLogic::switchToPlayerTurn,
                     m_mainWindow.get(), &MainWindow::handleSwitchToPlayerTurn);

    QObject::connect(m_gameLogic.get(), &GameLogic::finishIncomeState,
                     m_mainWindow.get(), &MainWindow::handleFinishIncomeState);

    QObject::connect(m_gameLogic.get(), &GameLogic::finishPurchaseState,
                     m_mainWindow.get(), &MainWindow::handleFinishPurchaseState);

    QObject::connect(m_gameLogic.get(), &GameLogic::finishWaitState,
                     m_mainWindow.get(), &MainWindow::handleFinishWaitState);

    // GameLogic -> NetworkManager
    QObject::connect(m_gameLogic.get(), &GameLogic::sendDiceRollResult,
                     m_network.get(), &NetworkManager::broadcastDiceRollResult);

    QObject::connect(m_gameLogic.get(), &GameLogic::finishIncomeState,
                     m_network.get(), &NetworkManager::broadcastFinishIncomeState);

    // mainWindow -> gameLogic
    QObject::connect(m_mainWindow.get(), &MainWindow::cardClickedForPurchase,
                     m_gameLogic.get(), &GameLogic::handleCardClickedForPurchase);

    QObject::connect(m_mainWindow.get(), &MainWindow::createPlayers,
                     m_gameLogic.get(), &GameLogic::handleCreatePlayers);

    QObject::connect(m_mainWindow.get(), &MainWindow::rollDiceButtonClicked,
                     m_gameLogic.get(), &GameLogic::handleRollDiceButtonClicked);

    QObject::connect(m_mainWindow.get(), &MainWindow::sendDiceRerollResponse,
                     m_gameLogic.get(), &GameLogic::receiveDiceRerollResponse);

    QObject::connect(m_mainWindow.get(), &MainWindow::skipButtonClicked,
                     m_gameLogic.get(), &GameLogic::handleSkipButtonClicked);

    // mainWindow -> NetworkManager
    // QObject::connect(m_mainWindow.get(), &MainWindow::broadcastJson,
    //                  m_network.get(), &NetworkManager::sendMessage);

}

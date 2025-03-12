#include "gamelogic.h"
#include "mainwindow.h"
#include "startmenu.h"


#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    GameLogic* gameLogic = new GameLogic();
    MainWindow* mainWindow = new MainWindow();
    StartMenu* startMenu = new StartMenu();

    QObject::connect(startMenu, &StartMenu::showMainWindow,
                     mainWindow, &MainWindow::handleShowMainWindow);

    QObject::connect(mainWindow, &MainWindow::createPlayers,
                     gameLogic, &GameLogic::handleCreatePlayers);

    QObject::connect(mainWindow, &MainWindow::rollButtonClicked,
                     gameLogic, &GameLogic::handleRollButtonClicked);

    QObject::connect(gameLogic, &GameLogic::buildStageFinished,
                     mainWindow, &MainWindow::updateCurrentPlayer);

    QObject::connect(gameLogic, &GameLogic::incomeStageFinished,
                     mainWindow, &MainWindow::startBuildStage);

    QObject::connect(mainWindow, &MainWindow::cardWidgetClicked,
                     gameLogic, &GameLogic::handleTryToBuyCard);

    QObject::connect(gameLogic, &GameLogic::playerBuildNewBuilding,
                     mainWindow, &MainWindow::displayPlayerNewCard);

    QObject::connect(mainWindow, &MainWindow::updatedPlayersPanel,
                     gameLogic, &GameLogic::prepateNextTurn);

    QObject::connect(gameLogic, &GameLogic::playerBalanceChanged,
                     mainWindow, &MainWindow::updatePlayerBalanceLabel);

    startMenu->show();

    return app.exec();
}

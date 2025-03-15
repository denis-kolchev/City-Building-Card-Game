#include "gamelogic.h"
#include "mainwindow.h"
#include "startmenu.h"


#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    auto gameLogic = std::make_shared<GameLogic>();
    auto mainWindow = std::make_shared<MainWindow>();
    auto startMenu = std::make_shared<StartMenu>();

    QObject::connect(startMenu.get(), &StartMenu::showMainWindow,
                     mainWindow.get(), &MainWindow::handleShowMainWindow);

    QObject::connect(mainWindow.get(), &MainWindow::createPlayers,
                     gameLogic.get(), &GameLogic::handleCreatePlayers);

    QObject::connect(mainWindow.get(), &MainWindow::rollButtonClicked,
                     gameLogic.get(), &GameLogic::handleRollButtonClicked);

    QObject::connect(gameLogic.get(), &GameLogic::buildStageFinished,
                     mainWindow.get(), &MainWindow::repaintPlayerPanel);

    QObject::connect(mainWindow.get(), &MainWindow::cardWidgetClicked,
                     gameLogic.get(), &GameLogic::handleTryToBuyCard);

    QObject::connect(gameLogic.get(), &GameLogic::playerBuildNewBuilding,
                     mainWindow.get(), &MainWindow::displayPlayerNewCard);

    QObject::connect(mainWindow.get(), &MainWindow::updatedPlayersPanel,
                     gameLogic.get(), &GameLogic::prepateNextTurn);

    QObject::connect(gameLogic.get(), &GameLogic::playerBalanceChanged,
                     mainWindow.get(), &MainWindow::updatePlayerBalanceLabel);

    QObject::connect(mainWindow.get(), &MainWindow::skipClicked,
                     gameLogic.get(), &GameLogic::moveToNextPlaer);

    QObject::connect(gameLogic.get(), &GameLogic::playerHasRailwayStation,
                     mainWindow.get(), &MainWindow::unlockRollTwoDiceButton);

    QObject::connect(gameLogic.get(), &GameLogic::playerBuildLandmark,
                     mainWindow.get(), &MainWindow::unlockPlayerLandmark);

    startMenu->show();

    return app.exec();
}

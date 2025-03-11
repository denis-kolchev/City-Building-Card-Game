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

    startMenu->show();

    return app.exec();
}

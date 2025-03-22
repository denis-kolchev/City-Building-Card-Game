#ifndef GAMEAPPLICATIONBUILDER_H
#define GAMEAPPLICATIONBUILDER_H

#include "gamelogic.h"
#include "gamemanager.h"
#include "mainwindow.h"
#include "startmenu.h"

class GameApplicationBuilder {
public:
    GameApplicationBuilder& withGameLogic();

    GameApplicationBuilder& withMainWindow();

    GameApplicationBuilder& withStartMenu();

    std::shared_ptr<GameApplication> build();

private:
    std::shared_ptr<GameLogic> gameLogic;
    std::shared_ptr<MainWindow> mainWindow;
    std::shared_ptr<StartMenu> startMenu;
};

#endif // GAMEAPPLICATIONBUILDER_H

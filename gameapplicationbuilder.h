#ifndef GAMEAPPLICATIONBUILDER_H
#define GAMEAPPLICATIONBUILDER_H

#include "logic/gamelogic.h"
#include "gameapplication.h"
#include "ui/mainwindow.h"
#include "ui/startmenu.h"

class GameApplicationBuilder
{
public:
    GameApplicationBuilder& withConfigReader();

    GameApplicationBuilder& withGameLogic();

    GameApplicationBuilder& withMainWindow();

    GameApplicationBuilder& withNetworkManager();

    GameApplicationBuilder& withStartMenu();

    std::shared_ptr<GameApplication> build();

private:
    std::shared_ptr<CardDataConfigReader>   m_configReader;
    std::shared_ptr<GameLogic>              m_gameLogic;
    std::shared_ptr<MainWindow>             m_mainWindow;
    std::shared_ptr<NetworkManager>         m_network;
    std::shared_ptr<StartMenu>              m_startMenu;
};

#endif // GAMEAPPLICATIONBUILDER_H

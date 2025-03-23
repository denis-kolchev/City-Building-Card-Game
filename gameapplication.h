#ifndef GAMEAPPLICATION_H
#define GAMEAPPLICATION_H

#include "carddataconfigreader.h"
#include "gamelogic.h"
#include "mainwindow.h"
#include "startmenu.h"

class GameApplication {
public:
    GameApplication(std::shared_ptr<CardDataConfigReader> configReader,
                    std::shared_ptr<GameLogic> logic,
                    std::shared_ptr<MainWindow> window,
                    std::shared_ptr<StartMenu> menu);

    void run();

private:
    void setupConnections();

private:
    std::shared_ptr<CardDataConfigReader> m_configReader;
    std::shared_ptr<GameLogic>            m_gameLogic;
    std::shared_ptr<MainWindow>           m_mainWindow;
    std::shared_ptr<StartMenu>            m_startMenu;

};
#endif // GAMEAPPLICATION_H

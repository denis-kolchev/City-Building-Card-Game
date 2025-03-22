#include "gameapplicationbuilder.h"

GameApplicationBuilder& GameApplicationBuilder::withGameLogic() {
    gameLogic = std::make_shared<GameLogic>();
    return *this;
}

GameApplicationBuilder& GameApplicationBuilder::withMainWindow() {
    mainWindow = std::make_shared<MainWindow>();
    return *this;
}

GameApplicationBuilder& GameApplicationBuilder::withStartMenu() {
    startMenu = std::make_shared<StartMenu>();
    return *this;
}

std::shared_ptr<GameApplication> GameApplicationBuilder::build() {
    return std::make_shared<GameApplication>(gameLogic, mainWindow, startMenu);
}

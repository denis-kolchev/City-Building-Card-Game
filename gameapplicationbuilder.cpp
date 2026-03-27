#include "gameapplicationbuilder.h"

#include <algorithm>

GameApplicationBuilder& GameApplicationBuilder::withConfigReader()
{
    m_configReader = std::make_shared<CardDataConfigReader>();
    return *this;
}

GameApplicationBuilder& GameApplicationBuilder::withGameLogic()
{
    m_gameLogic = std::make_shared<GameLogic>();
    return *this;
}

GameApplicationBuilder& GameApplicationBuilder::withMainWindow()
{
    m_mainWindow = std::make_shared<MainWindow>();
    return *this;
}

GameApplicationBuilder& GameApplicationBuilder::withNetworkManager()
{
    m_network = std::make_shared<NetworkManager>();
    return *this;
}

GameApplicationBuilder& GameApplicationBuilder::withStartMenu()
{
    m_startMenu = std::make_shared<StartMenu>();
    return *this;
}

GameApplicationBuilder& GameApplicationBuilder::withOfflinePlayerCount(int count)
{
    m_offlinePlayerCount = std::clamp(count, 2, 5);
    return *this;
}

std::shared_ptr<GameApplication> GameApplicationBuilder::build()
{
    return std::make_shared<GameApplication>(m_configReader,
                                             m_gameLogic,
                                             m_mainWindow,
                                             m_network,
                                             m_startMenu,
                                             m_offlinePlayerCount);
}

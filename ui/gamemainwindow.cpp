#include "GameMainWindow.h"
#include "gameconfig.h"

#include <QDockWidget>
#include <QTextEdit>
#include <QTreeWidget>
#include <QPlainTextEdit>
#include <QMenuBar>

GameMainWindow::GameMainWindow(GameConfig* gameConfig,
                               QMainWindow* parent)
{
    m_playersViewCount = gameConfig->getPlayersCount();
    m_playersNames = gameConfig->getPlayersNames();
    createDockWindows();

    int windowMinWidth = 1168;
    int windowMinHeight = 755;
    setMinimumSize(windowMinWidth, windowMinHeight);
}

GameMainWindow::~GameMainWindow()
{

}

void GameMainWindow::createDockWindows()
{
    QDockWidget* shopWindow = new QDockWidget(tr("Card Shop"), this);
    shopWindow->setAllowedAreas(Qt::LeftDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, shopWindow);

    for (int i = 0; i < m_playersViewCount; ++i) {
        QDockWidget* playerWindow = new QDockWidget(m_playersNames[i], this);
        addDockWidget(Qt::RightDockWidgetArea, playerWindow);
    }
}

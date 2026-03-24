#ifndef GAMEMAINWINDOW_H
#define GAMEMAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QVector>
#include <QJsonDocument>

#include <qtypes.h>

class GameConfig;

class GameMainWindow : public QMainWindow
{
public:
    explicit GameMainWindow(GameConfig* gameConfig,
                            QMainWindow *p = nullptr);

    ~GameMainWindow();

private:
    void createDockWindows();

private:
    QGraphicsView* m_shop;
    QVector<QGraphicsView*> m_playersViews;
    qsizetype m_playersViewCount;
    QList<QString> m_playersNames;
};

#endif // GAMEMAINWINDOW_H

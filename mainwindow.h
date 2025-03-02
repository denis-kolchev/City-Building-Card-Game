#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gamelogic.h"

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private:
    void createCards();

private:
    GameLogic m_gameLogic;
};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "cardreserve.h"

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
    CardReserve reserve;
};
#endif // MAINWINDOW_H

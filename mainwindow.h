#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "cardinfo.h"

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
    QVector<CardInfo*> baseGameCardsInfo;
    QVector<CardInfo*> extensionCardsInfo;
    QVector<CardInfo*> expansionCardsInfo;
};
#endif // MAINWINDOW_H

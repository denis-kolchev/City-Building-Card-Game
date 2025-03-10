#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QVBoxLayout>

#include "carddataconfigreader.h"

using CardsList = QVector<std::shared_ptr<Card>>;
using CardsLayout = QHBoxLayout;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private slots:
    void handleCardClick();

private:
    void placeCards(CardsList &cards, CardsLayout &layout);

};
#endif // MAINWINDOW_H

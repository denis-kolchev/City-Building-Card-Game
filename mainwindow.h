#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QVBoxLayout>

#include "carddataconfigreader.h"

using CardsList = QVector<std::shared_ptr<Card>>;
using CardsLayout = QHBoxLayout;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QMainWindow *parent = nullptr);

    ~MainWindow();

public slots:
    void handleShowMainWindow(uchar numPlayers);

    void updateCurrentPlayer(int currentPlayerId);

    void updateDiceResultLabel(uchar dice);

signals:
    void buyButtonClicked();

    void createPlayers(QList<QString> playerNames);

    void rollButtonClicked(uchar dice);

    void skipClicked();

private slots:
    void handleCardClick();

    void onRollOneDiceClicked();

    void onRollTwoDiceClicked();

    void onSkipClicked();

private:
    QWidget* createPlayerView(uchar playerId);

    void placeCards(CardsList &cards, CardsLayout &layout);

private:
    QVector<QLabel*> m_diceResultLabels;
    int m_numPlayers;
    int m_currentPlayerId;
};
#endif // MAINWINDOW_H

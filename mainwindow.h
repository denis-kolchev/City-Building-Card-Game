#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
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
    void displayPlayerNewCard(std::shared_ptr<Card> card);

    void handleShowMainWindow(uchar numPlayers);

    void startBuildStage();

    void updateCurrentPlayer(int currentPlayerId);

    void updateDiceResultLabel(uchar dice);

    void updatePlayerBalanceLabel(uchar balance);

signals:
    void buyButtonClicked();

    void cardWidgetClicked(QString cardTitle);

    void createPlayers(QList<QString> playerNames);

    void rollButtonClicked(uchar dice);

    void skipClicked();

    void updatedPlayersPanel();

private slots:
    void handleCardClick(QString cardTitle);

    void onRollOneDiceClicked();

    void onRollTwoDiceClicked();

    void onSkipClicked();

private:
    QWidget* createPlayerView(uchar playerId);

    void placeCards(CardsList &cards, CardsLayout &layout);

private:
    QVector<QLabel*> m_playerBalanceLabels;
    QVector<QLabel*> m_diceResultLabels;
    QVector<QHBoxLayout*> m_buildsLayout;
    QVector<QHBoxLayout*> m_landmarksLayout;
    QVector<QPushButton*> m_rollOneDiceButtons;
    QVector<QPushButton*> m_rollTwoDiceButtons;
    int m_numPlayers;
    int m_currentPlayerId;
};
#endif // MAINWINDOW_H

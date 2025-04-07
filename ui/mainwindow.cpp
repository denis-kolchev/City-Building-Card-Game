#include "mainwindow.h"

#include <QDir>
#include <QLabel>
#include <QMessageBox>
#include <QScrollArea>
#include <QSignalTransition>
#include <QVector>

#include <QTabWidget>
#include <QtWidgets/qapplication.h>

MainWindow::MainWindow(QMainWindow *parent)
    : QMainWindow(parent)
    , m_centralWidget(new QWidget(this))
    , m_mainLayout(new QHBoxLayout(m_centralWidget))
    , m_bankCardsArea(new QScrollArea())
    , m_bankScrollWidget(new CardScrollWidget())
    , m_bankLayout(new QHBoxLayout())
    , m_tabWidget(new QTabWidget(this))
{
    connect(m_bankScrollWidget, &CardScrollWidget::cardSignalClicked,
            this, &MainWindow::cardClickedForPurchase);

    m_bankCardsArea->setWidget(m_bankScrollWidget);
    m_bankCardsArea->setWidgetResizable(true);

    m_mainLayout->addWidget(m_bankCardsArea);
    m_mainLayout->addWidget(m_tabWidget);

    m_centralWidget->setLayout(m_mainLayout);

    setCentralWidget(m_centralWidget);

    setWindowTitle(tr("City Building Card Game"));
    resize(1366, 768);
}

MainWindow::~MainWindow()
{
}

void MainWindow::handleFinishIncomeState(int playerId)
{
    qDebug() << tr("It's time to finish income state for this player: %1").arg(playerId);
    if (playerId >= 0 && playerId < m_playerPages.size()) {
        auto& page = m_playerPages[playerId];
        page->getOneDiceButton().setEnabled(false);
        page->getTwoDiceButton().setEnabled(false);
        page->getSkipButton().setEnabled(true);
    }
}

void MainWindow::handleFinishPurchaseState(int playerId)
{
    if (playerId >= 0 && playerId < m_playerPages.size()) {
        auto& page = m_playerPages[playerId];
        page->getOneDiceButton().setEnabled(false);
        page->getTwoDiceButton().setEnabled(false);
        page->getSkipButton().setEnabled(false);
    }
}

void MainWindow::handleFinishWaitState(int playerId)
{
    if (playerId >= 0 && playerId < m_playerPages.size()) {
        auto& page = m_playerPages[playerId];
        page->getOneDiceButton().setEnabled(true);
        page->getSkipButton().setEnabled(false);
    }

    for (int pageId = 0; pageId < m_playerPages.size(); ++pageId) {
        m_tabWidget->setTabIcon(pageId, createCircleIcon(m_inactivePlayerColor));
    }

    m_tabWidget->setTabIcon(playerId, createCircleIcon(m_activePlayerColor));
    m_tabWidget->setCurrentIndex(playerId);

}

void MainWindow::handleGameWon(int playerId)
{
    QMessageBox msgBox(this);
    msgBox.setWindowTitle(tr("Game Over"));
    msgBox.setText(QString(tr("Player %1 won!")).arg(char(playerId + 'A')));
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setWindowFlags(Qt::WindowStaysOnTopHint);
    msgBox.exec();

    QApplication::quit(); // Close the entire app
}

void MainWindow::handleRequestDiceRerollConfirmation(int playerId, QVector<int> rools)
{
    QString diceText;
    if (rools[1] != 0) {
        diceText = QString("%1 + %2 = %3").arg(rools[0]).arg(rools[1]).arg(rools[0] + rools[1]);
    } else {
        diceText = QString("%1").arg(rools[0]);
    }

    QMessageBox msgBox(this);
    msgBox.setWindowTitle(tr("Reroll Request"));
    msgBox.setText(
        QString("Player %1, would you like to reroll the dice? (Current: %2)")
            .arg(char(playerId + 'A'))
            .arg(diceText)
    );

    msgBox.setIcon(QMessageBox::Question);
    msgBox.setWindowFlags(Qt::WindowStaysOnTopHint);

    msgBox.addButton(QMessageBox::Yes);
    msgBox.addButton(QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::NoButton);

    msgBox.exec();

    bool isConfirmed = (msgBox.clickedButton() == msgBox.button(QMessageBox::Yes));
    emit sendDiceRerollResponse(rools, isConfirmed);
}

void MainWindow::handleShowMainWindow(int playersCount)
{
    // Create a tab for each player
    char playerName = 'A';
    QVector<QString> playerNames(playersCount);
    for (int i = 0; i < playerNames.size(); ++i, ++playerName) {
        auto* playerPage = createPlayerPage(i);
        m_tabWidget->addTab(playerPage, QString("Player %1").arg(playerName));
        m_tabWidget->setTabIcon(i, createCircleIcon(m_inactivePlayerColor)); // red (inactive)
        m_playerPages.append(playerPage);
    }

    m_tabWidget->setTabIcon(0, createCircleIcon(m_activePlayerColor));

    emit createPlayers(playersCount);

    setupStateMachines();

    show();
}

void MainWindow::handleSwitchToPlayerTurn(int playerId)
{
    // sets set
    m_tabWidget->setCurrentIndex(playerId);

    if (playerId >= 0 && playerId < m_playerStateMachines.size()) {
        m_playerStateMachines[playerId].m_stateMachine->postEvent(new QEvent(QEvent::Type(QEvent::User + 2)));
    }
}

void MainWindow::receiveBankLoosesCard(std::shared_ptr<Card> card)
{
    if (card->activationValues().contains(0)) {
        return;
    }

    m_bankScrollWidget->removeCards({card});
}

void MainWindow::receiveBankGetsCard(std::shared_ptr<Card> card)
{
    if (card->activationValues().contains(0)) {
        for (int playerId = 0; playerId < m_playerPages.size(); ++playerId) {
            auto playerLandmarks = m_playerPages[playerId]->getLandmarkScrollWidget();
            if (!playerLandmarks->getStacks().contains(card->id())) {
                playerLandmarks->addCard(card);
            }
        }
        return;
    }

    m_bankScrollWidget->placeCards({card});
}

void MainWindow::receiveCardPurchaseFailed(int playerId, CardId cardId, QString message)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(tr("Purchase Failed"));
    msgBox.setText(
        QString("Player %1 cannot purchase Card [%2]!\n\n%3")
            .arg(char(playerId + 'A'))
            .arg(int(cardId))
            .arg(message)
        );

    msgBox.addButton(QMessageBox::Ok);
    msgBox.setWindowFlags(Qt::WindowStaysOnTopHint);

    msgBox.exec();
}

void MainWindow::receiveDiceRollResult(int playerId, QVector<int> rolls)
{
    for (auto playePage : m_playerPages) {
        playePage->setDiceResult(rolls[0], rolls[1]);
    }
}

void MainWindow::receivePlayerBalanceChanged(int playerId, int balance)
{
    m_playerPages[playerId]->setPlayerBalance(balance);
}

void MainWindow::receivePlayerGetsCard(int playerId, std::shared_ptr<Card> card)
{
    auto playerPage = m_playerPages[playerId];
    if (card->activationValues().contains(0)) {
        if (playerPage->getLandmarkScrollWidget()->getStacks().contains(card->id())) {
            playerPage->turnOnCardStack(card->id());
        }
        return;
    }

    playerPage->placeCards({card});
}

void MainWindow::receivePlayerLoosesCard(int playerId, std::shared_ptr<Card> card)
{
    auto playerPage = m_playerPages[playerId];
    if (card->activationValues().contains(0)) {
        if (playerPage->getLandmarkScrollWidget()->getStacks().contains(card->id())) {
            playerPage->turnOffCardStack(card->id());
        }
        return;
    }

    playerPage->removeCards({card});
}

void MainWindow::receiveRollTwoDiceAvailable(int playerId)
{
    if (playerId >= 0 && playerId < m_playerPages.size()) {
        auto& page = m_playerPages[playerId];
        page->getTwoDiceButton().setEnabled(true);
    }
}

void MainWindow::centerWindow()
{
    // Get the screen geometry
    QScreen *screen = QApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();

    // Calculate the center position
    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;

    // Move the window to the center
    move(x, y);
    hide();
}

QIcon MainWindow::createCircleIcon(const QColor color, qsizetype size)
{
    QPixmap iconPixmap(size, size);
    iconPixmap.fill(Qt::transparent);
    QPainter painter(&iconPixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(color);
    painter.drawEllipse(0, 0, size, size);
    return QIcon(iconPixmap);
}

PlayerPage* MainWindow::createPlayerPage(uchar playerId)
{
    PlayerPage* playerPage = new PlayerPage(playerId);
    connect(playerPage, &PlayerPage::rollOneDiceClicked, this, [this]() { emit rollDiceButtonClicked(1); });
    connect(playerPage, &PlayerPage::rollTwoDiceClicked, this, [this]() { emit rollDiceButtonClicked(2); });
    connect(playerPage, &PlayerPage::skipClicked, this, &MainWindow::skipButtonClicked);
    connect(playerPage->getLandmarkScrollWidget(), &CardScrollWidget::cardSignalClicked, this, &MainWindow::cardClickedForPurchase);
    return playerPage;
}

void MainWindow::setupStateMachines()
{
    m_playerStateMachines.resize(m_playerPages.size());

    for (int playerId = 0; playerId < m_playerPages.size(); ++playerId) {
        auto& playerStateMachine = m_playerStateMachines[playerId];

        // Create states
        playerStateMachine.m_stateMachine = new QStateMachine(this);
        playerStateMachine.m_waitState = new QState(playerStateMachine.m_stateMachine);
        playerStateMachine.m_incomeState = new QState(playerStateMachine.m_stateMachine);
        playerStateMachine.m_purchaseState = new QState(playerStateMachine.m_stateMachine);

        // Configure state behaviors
        playerStateMachine.m_waitState->assignProperty(&m_playerPages[playerId]->getOneDiceButton(), "enabled", false);
        playerStateMachine.m_waitState->assignProperty(&m_playerPages[playerId]->getTwoDiceButton(), "enabled", false);
        playerStateMachine.m_waitState->assignProperty(&m_playerPages[playerId]->getSkipButton(), "enabled", false);

        playerStateMachine.m_incomeState->assignProperty(&m_playerPages[playerId]->getOneDiceButton(), "enabled", true);
        playerStateMachine.m_incomeState->assignProperty(&m_playerPages[playerId]->getTwoDiceButton(), "enabled", false);
        playerStateMachine.m_incomeState->assignProperty(&m_playerPages[playerId]->getSkipButton(), "enabled", false);

        playerStateMachine.m_purchaseState->assignProperty(&m_playerPages[playerId]->getOneDiceButton(), "enabled", false);
        playerStateMachine.m_purchaseState->assignProperty(&m_playerPages[playerId]->getTwoDiceButton(), "enabled", false);
        playerStateMachine.m_purchaseState->assignProperty(&m_playerPages[playerId]->getSkipButton(), "enabled", true);

        // Add states to machine
        playerStateMachine.m_stateMachine->addState(playerStateMachine.m_waitState);
        playerStateMachine.m_stateMachine->addState(playerStateMachine.m_incomeState);
        playerStateMachine.m_stateMachine->addState(playerStateMachine.m_purchaseState);

        // Set initial state
        if (playerId == 0) {
            playerStateMachine.m_stateMachine->setInitialState(playerStateMachine.m_incomeState);
        } else {
            playerStateMachine.m_stateMachine->setInitialState(playerStateMachine.m_waitState);
        }

        setupTransitionsForPlayer(playerId);

        playerStateMachine.m_stateMachine->start();
    }

}

void MainWindow::setupTransitionsForPlayer(int playerId)
{
    auto& playerStateMachine = m_playerStateMachines[playerId];

    // Transition from ANY state to WaitState when signal arrives
    playerStateMachine.toWaitState = new QSignalTransition(this, &MainWindow::handleFinishPurchaseState);
    playerStateMachine.toWaitState->setTargetState(playerStateMachine.m_waitState);
    playerStateMachine.m_stateMachine->addTransition(playerStateMachine.toWaitState);

    // Transition from ANY state to IncomeState when signal arrives
    playerStateMachine.toIncomeState = new QSignalTransition(this, &MainWindow::handleFinishWaitState);
    playerStateMachine.toIncomeState->setTargetState(playerStateMachine.m_incomeState);
    playerStateMachine.m_stateMachine->addTransition(playerStateMachine.toIncomeState);

    // Transition from ANY state to PurchaseState when signal arrives
    playerStateMachine.toPurchaseState = new QSignalTransition(this, &MainWindow::handleFinishIncomeState);
    playerStateMachine.toPurchaseState->setTargetState(playerStateMachine.m_purchaseState);
    playerStateMachine.m_stateMachine->addTransition(playerStateMachine.toPurchaseState);
}

void MainWindow::handleCardClick(CardId id)
{
    emit cardClickedForPurchase(id);

    // if (m_stateMachine->configuration().contains(m_purchaseState)) {
    //     emit cardClickedForPurchase(id);
    //     return;
    // }

    // QMessageBox msgBox(this);
    // msgBox.setWindowTitle(tr("You can't buy it yet"));
    // msgBox.setText(QString(tr("You need to press the \"roll dice\" button first.\n\nWait until it becomes active or press it right now.")));
    // msgBox.setStandardButtons(QMessageBox::Ok);
    // msgBox.exec();
}

#include "startmenu.h"

#include <QVBoxLayout>
#include <QSpinBox>
#include <QPushButton>
#include <QLabel>
#include <QApplication>
#include <QRect>
#include <QScreen>

StartMenu::StartMenu(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Start Menu");

    // Layout
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Number of players selection
    QLabel *numPlayersLabel = new QLabel("Number of Players:", this);
    numPlayersLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(numPlayersLabel);

    QSpinBox *numPlayersSpinBox = new QSpinBox(this);
    numPlayersSpinBox->setRange(2, 5); // Set range from 2 to 5
    numPlayersSpinBox->setValue(2);    // Default value
    layout->addWidget(numPlayersSpinBox);

    // Start Game button
    QPushButton *startButton = new QPushButton("Start the Game", this);
    layout->addWidget(startButton);

    // Connect the button to the slot
    connect(startButton, &QPushButton::clicked, this, [this, numPlayersSpinBox]() {
        uchar numPlayers = static_cast<uchar>(numPlayersSpinBox->value());
        emit showMainWindow(numPlayers);
        close(); // Close the start menu
    });

    setLayout(layout);

    setFixedSize(300, 130);
    centerWindow();
    //TODO should call it when placment of cards is finished
    //setWindowFlags(Qt::Window | Qt::WindowStaysOnTopHint);
    //qDebug() << "3. mainWindow is made correctly";
}

void StartMenu::centerWindow()
{
    // Get the screen geometry
    QScreen *screen = QApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();

    // Calculate the center position
    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;

    // Move the window to the center
    move(x, y);
}

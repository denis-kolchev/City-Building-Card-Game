#include "startmenu.h"

#include "mainwindow.h"

#include <QVBoxLayout>
#include <QSpinBox>
#include <QPushButton>
#include <QLabel>

StartMenu::StartMenu(QWidget *parent)
    : QWidget(parent) {
    setWindowTitle("Start Menu");
    setGeometry(200, 200, 300, 200);

    // Layout
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Number of players selection
    QLabel *numPlayersLabel = new QLabel("Number of Players:", this);
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
        int numPlayers = numPlayersSpinBox->value();
        MainWindow *mainWindow = new MainWindow(numPlayers);
        mainWindow->show();
        this->close(); // Close the start menu
    });

    setLayout(layout);
}

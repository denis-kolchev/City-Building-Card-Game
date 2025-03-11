#include "startmenu.h"

#include <QVBoxLayout>
#include <QSpinBox>
#include <QPushButton>
#include <QLabel>

StartMenu::StartMenu(QWidget *parent)
    : QWidget(parent) {
    setWindowTitle("Start Menu");

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
        uchar numPlayers = static_cast<uchar>(numPlayersSpinBox->value());
        emit showMainWindow(numPlayers);
        close(); // Close the start menu
    });

    setLayout(layout);
}

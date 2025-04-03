#include "startmenu.h"
#include <QPushButton>
#include <QApplication>
#include <QRect>
#include <QScreen>
#include <QIntValidator>

StartMenu::StartMenu(QWidget *parent)
    : QWidget(parent),
    m_tabWidget(new QTabWidget(this)),
    m_offlineTab(new QWidget()),
    m_onlineTab(new QWidget()),
    m_offlineLayout(new QVBoxLayout(m_offlineTab)),

    m_numPlayersLabel(new QLabel("Number of Players:", m_offlineTab)),
    m_numPlayersSpinBox(new QSpinBox(m_offlineTab)),

    m_startButton(new QPushButton("Start Offline Game", m_offlineTab)),
    m_onlineLayout(new QVBoxLayout(m_onlineTab)),

    m_numPlayersOnlineLabel(new QLabel("Number of Players:", m_onlineTab)),
    m_numPlayersOnlineSpinBox(new QSpinBox(m_onlineTab)),

    m_ipLabel(new QLabel("Server IP:", m_onlineTab)),
    m_ipInput(new QLineEdit(m_onlineTab)),
    m_portLabel(new QLabel("Server Port:", m_onlineTab)),
    m_portInput(new QLineEdit(m_onlineTab)),
    m_connectButton(new QPushButton("Connect to Server", m_onlineTab))
{
    setWindowTitle("Game Start Menu");

    // Setup tabs
    setupOfflineTab();
    setupOnlineTab();

    m_tabWidget->addTab(m_offlineTab, "Offline Game");
    m_tabWidget->addTab(m_onlineTab, "Online Game");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_tabWidget);
    setLayout(mainLayout);

    setFixedSize(350, 300);
    centerWindow();
}

void StartMenu::setupOfflineTab()
{
    m_offlineLayout->addStretch();

    m_numPlayersLabel->setAlignment(Qt::AlignCenter);
    m_offlineLayout->addWidget(m_numPlayersLabel);

    m_numPlayersSpinBox->setRange(2, 5);
    m_numPlayersSpinBox->setValue(2);
    m_offlineLayout->addWidget(m_numPlayersSpinBox);

    m_startButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_offlineLayout->addWidget(m_startButton);

    connect(m_startButton, &QPushButton::clicked, this, [this]() {
        emit showMainWindow(m_numPlayersSpinBox->value());
        close();
    });

    m_offlineLayout->addStretch();
}

void StartMenu::setupOnlineTab()
{
    m_onlineLayout->addStretch();

    // IP input setup
    m_ipLabel->setAlignment(Qt::AlignCenter);
    m_onlineLayout->addWidget(m_ipLabel);

    m_ipInput->setPlaceholderText("127.0.0.1");
    m_onlineLayout->addWidget(m_ipInput);

    // Port input setup
    m_portLabel->setAlignment(Qt::AlignCenter);
    m_onlineLayout->addWidget(m_portLabel);

    m_portInput->setPlaceholderText("12345");
    m_portInput->setValidator(new QIntValidator(1, 65535, this));
    m_onlineLayout->addWidget(m_portInput);

    // copy paste isn't great, but it works by far
    m_numPlayersOnlineLabel->setAlignment(Qt::AlignCenter);
    m_onlineLayout->addWidget(m_numPlayersOnlineLabel);

    m_numPlayersOnlineSpinBox->setRange(2, 5);
    m_numPlayersOnlineSpinBox->setValue(2);
    m_onlineLayout->addWidget(m_numPlayersOnlineSpinBox);

    // Connect button
    m_connectButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_onlineLayout->addWidget(m_connectButton);

    connect(m_connectButton, &QPushButton::clicked, this, [this]() {
        QString ip = m_ipInput->text().isEmpty() ? "127.0.0.1" : m_ipInput->text();
        int port = m_portInput->text().isEmpty() ? 12345 : m_portInput->text().toInt();
        emit connectToServer(ip, port);
    });

    m_onlineLayout->addStretch();
}

void StartMenu::centerWindow()
{
    QScreen *screen = QApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();

    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;

    move(x, y);
}

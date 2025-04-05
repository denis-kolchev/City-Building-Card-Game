#include "startmenu.h"


#include <QApplication>
#include <QIntValidator>
#include <QMessageBox>
#include <QPushButton>
#include <QRect>
#include <QScreen>

StartMenu::StartMenu(QWidget *parent)
    : QWidget(parent),
    m_tabWidget(new QTabWidget(this)),
    m_offlineTab(new QWidget()),
    m_serverTab(new QWidget()),
    m_clientTab(new QWidget()),

    m_offlineLayout(new QVBoxLayout(m_offlineTab)),
    m_numPlayersLabel(new QLabel("Number of Players:", m_offlineTab)),
    m_numPlayersSpinBox(new QSpinBox(m_offlineTab)),

    m_clientTabLayout(new QVBoxLayout(m_clientTab)),
    m_clientTabIpLabel(new QLabel("Server IP:", m_clientTab)),
    m_cleintTabIpInput(new QLineEdit(m_clientTab)),
    m_cleintTabPortLabel(new QLabel("Server Port:", m_clientTab)),
    m_cleintTabPortInput(new QLineEdit(m_clientTab)),
    m_cleintTabConnectButton(new QPushButton("Connect to Server", m_serverTab)),

    m_startButton(new QPushButton("Start Offline Game", m_offlineTab)),
    m_serverTabLayout(new QVBoxLayout(m_serverTab)),

    m_numPlayersServerTabLabel(new QLabel("Number of Players:", m_serverTab)),
    m_numPlayersServerTabSpinBox(new QSpinBox(m_serverTab)),

    m_serverTabIpLabel(new QLabel("Server IP:", m_serverTab)),
    m_serverTabOpInput(new QLineEdit(m_serverTab)),
    m_serverTabPortLabel(new QLabel("Server Port:", m_serverTab)),
    m_serverTabPortInput(new QLineEdit(m_serverTab)),
    m_serverTabConnectButton(new QPushButton("Create Server", m_serverTab))
{
    setWindowTitle("Game Start Menu");

    // Setup tabs
    setupOfflineTab();
    setupServerTab();
    setupClientTab();

    m_tabWidget->addTab(m_offlineTab, tr("Offline Game"));
    m_tabWidget->addTab(m_serverTab, tr("Create Server"));
    m_tabWidget->addTab(m_clientTab, tr("Connect to Server"));

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_tabWidget);
    setLayout(mainLayout);

    setFixedSize(450, 300);
    centerWindow();
}

void StartMenu::showMessage(const QString &message)
{
    QMessageBox::information(this, "Information", message);
}

void StartMenu::setupClientTab()
{
    m_clientTabLayout->addStretch(); // center layout elements

    // IP input setup
    m_clientTabIpLabel->setAlignment(Qt::AlignCenter);
    m_clientTabLayout->addWidget(m_clientTabIpLabel);

    m_cleintTabIpInput->setPlaceholderText("127.0.0.1");
    m_clientTabLayout->addWidget(m_cleintTabIpInput);

    // Port input setup
    m_cleintTabPortLabel->setAlignment(Qt::AlignCenter);
    m_clientTabLayout->addWidget(m_cleintTabPortLabel);

    m_cleintTabPortInput->setPlaceholderText("12345");
    m_cleintTabPortInput->setValidator(new QIntValidator(1, 65535, this));
    m_clientTabLayout->addWidget(m_cleintTabPortInput);

    m_cleintTabConnectButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_clientTabLayout->addWidget(m_cleintTabConnectButton);

    connect(m_cleintTabConnectButton, &QPushButton::clicked, this, [this]() {
        QString ip = m_cleintTabIpInput->text().isEmpty() ? "127.0.0.1" : m_cleintTabIpInput->text();
        int port = m_cleintTabPortInput->text().isEmpty() ? 12345 : m_cleintTabPortInput->text().toInt();
        emit onCreateClient(ip, port);
    });

    m_clientTabLayout->addStretch(); // center layout elements
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

void StartMenu::setupServerTab()
{
    m_serverTabLayout->addStretch();

    // IP input setup
    m_serverTabIpLabel->setAlignment(Qt::AlignCenter);
    m_serverTabLayout->addWidget(m_serverTabIpLabel);

    m_serverTabOpInput->setPlaceholderText("127.0.0.1");
    m_serverTabLayout->addWidget(m_serverTabOpInput);

    // Port input setup
    m_serverTabPortLabel->setAlignment(Qt::AlignCenter);
    m_serverTabLayout->addWidget(m_serverTabPortLabel);

    m_serverTabPortInput->setPlaceholderText("12345");
    m_serverTabPortInput->setValidator(new QIntValidator(1, 65535, this));
    m_serverTabLayout->addWidget(m_serverTabPortInput);

    // copy paste isn't great, but it works by far
    m_numPlayersServerTabLabel->setAlignment(Qt::AlignCenter);
    m_serverTabLayout->addWidget(m_numPlayersServerTabLabel);

    m_numPlayersServerTabSpinBox->setRange(2, 5);
    m_numPlayersServerTabSpinBox->setValue(2);
    m_serverTabLayout->addWidget(m_numPlayersServerTabSpinBox);

    // Connect button
    m_serverTabConnectButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_serverTabLayout->addWidget(m_serverTabConnectButton);

    connect(m_serverTabConnectButton, &QPushButton::clicked, this, [this]() {
        QString ip = m_serverTabOpInput->text().isEmpty() ? "127.0.0.1" : m_serverTabOpInput->text();
        int port = m_serverTabPortInput->text().isEmpty() ? 12345 : m_serverTabPortInput->text().toInt();
        emit onCreateServer(ip, port);
    });

    m_serverTabLayout->addStretch();
}

void StartMenu::centerWindow()
{
    QScreen *screen = QApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();

    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;

    move(x, y);
}

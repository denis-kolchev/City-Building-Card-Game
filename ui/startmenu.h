#ifndef STARTMENU_H
#define STARTMENU_H

#include <QWidget>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QLineEdit>

class StartMenu : public QWidget {
    Q_OBJECT

public:
    StartMenu(QWidget *parent = nullptr);

public slots:
    void showMessage(const QString &message);

signals:
    void onCreateServer(const QString& ip, quint16 port);

    void onCreateClient(const QString& op, quint16 port);

    void showMainWindow(int numPlayers);

private:
    void centerWindow();
    void setupClientTab();
    void setupOfflineTab();
    void setupServerTab();

private:
    QTabWidget *m_tabWidget;
    QWidget *m_offlineTab;
    QWidget *m_serverTab;
    QWidget *m_clientTab;

    // Offline tab widgets
    QVBoxLayout *m_offlineLayout;
    QLabel *m_numPlayersLabel;
    QSpinBox* m_numPlayersSpinBox;
    QPushButton *m_startButton;

    // Online tab widgets (Server)
    QVBoxLayout *m_serverTabLayout;
    QLabel *m_numPlayersServerTabLabel;
    QSpinBox* m_numPlayersServerTabSpinBox;

    QLabel *m_serverTabIpLabel;
    QLineEdit *m_serverTabOpInput;
    QLabel *m_serverTabPortLabel;
    QLineEdit *m_serverTabPortInput;
    QPushButton *m_serverTabConnectButton;

    // Client Tab
    QVBoxLayout *m_clientTabLayout;
    QLabel *m_clientTabIpLabel;
    QLineEdit *m_cleintTabIpInput;
    QLabel *m_cleintTabPortLabel;
    QLineEdit *m_cleintTabPortInput;
    QPushButton *m_cleintTabConnectButton;
};

#endif // STARTMENU_H

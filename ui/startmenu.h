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

signals:
    void showMainWindow(int numPlayers);
    void connectToServer(const QString& ip, int port);  // New signal for online game

private:
    void centerWindow();
    void setupOfflineTab();
    void setupOnlineTab();

private:
    QTabWidget *m_tabWidget;
    QWidget *m_offlineTab;
    QWidget *m_onlineTab;

    // Offline tab widgets
    QVBoxLayout *m_offlineLayout;
    QLabel *m_numPlayersLabel;
    QSpinBox* m_numPlayersSpinBox;
    QPushButton *m_startButton;

    // Online tab widgets
    QVBoxLayout *m_onlineLayout;
    QLabel *m_ipLabel;
    QLineEdit *m_ipInput;
    QLabel *m_portLabel;
    QLineEdit *m_portInput;
    QPushButton *m_connectButton;
};

#endif // STARTMENU_H

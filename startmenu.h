#ifndef STARTMENU_H
#define STARTMENU_H

#include <QWidget>

class StartMenu : public QWidget {
    Q_OBJECT

public:
    StartMenu(QWidget *parent = nullptr);

signals:
    void showMainWindow(uchar numPlayers);

};

#endif // STARTMENU_H

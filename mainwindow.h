#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private:
    void createCards();

private:
};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "game.h"
#include "mainmenu.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    MainMenu* mainMenu;
    Game* game;

    void showMainMenu();
    void startGame();
};

#endif // MAINWINDOW_H

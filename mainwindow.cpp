#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    game = new Game(this);
    game->show();
    /*
    mainMenu = new MainMenu(this);
    setCentralWidget(mainMenu);  // 设置主菜单界面
    mainMenu->show();

    connect(mainMenu, &MainMenu::startGame, this, &MainWindow::startGame);*/
}

MainWindow::~MainWindow()
{
    delete mainMenu;

}

void MainWindow::startGame()
{

}

void MainWindow::showMainMenu()
{

}

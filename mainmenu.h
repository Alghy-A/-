#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QPushButton>

class MainMenu : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

signals:
    void startGame();  // 信号，用于游戏开始

private:
    QPushButton* startButton;  // 开始按钮
};

#endif // MAINMENU_H

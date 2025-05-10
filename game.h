#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include<QGraphicsView>
#include"gamescene.h"
#include"player.h"
#include"playercontroller.h"
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class Game;
}
QT_END_NAMESPACE

class Game : public QWidget
{
    Q_OBJECT

public:
    Game(QWidget *parent = nullptr);
    ~Game();

public slots:
    void restartGame();

private:
    Ui::Game *ui;
    QGraphicsView *view;
    GameScene *scene;
    Player* player;
    PlayerController* controller;
    QTimer* timer;
};
#endif // GAME_H

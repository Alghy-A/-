#include "gamescene.h"
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QGraphicsPixmapItem>
#include"platform.h"

GameScene::GameScene(QObject* parent) : QGraphicsScene(parent)
{
    QPixmap background(":/pictures/background/background.jpg");
    backgroundItem = addPixmap(background);
    backgroundItem->setPos(0, 0);  // 设置初始位置

    addItem(new Platform(300, 450, 120, 20));
    addItem(new Platform(600, 370, 150, 20));
    addItem(new Platform(900, 300, 100, 20));

}

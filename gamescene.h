#ifndef GAMESCENE_H
#define GAMESCENE_H
#pragma once
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include<QKeyEvent>
#include<QTimer>


class GameScene : public QGraphicsScene
{
public:
    GameScene(QObject* parent = nullptr);


private:
    QGraphicsPixmapItem* backgroundItem;
    int backgroundX = 0;
};

#endif // GAMESCENE_H

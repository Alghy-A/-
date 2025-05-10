#pragma once
#include <QGraphicsPixmapItem>
#include"platform.h"
#include <QTimer>
#include <QVector>

class Player : public QGraphicsPixmapItem , public QObject {
public:
    Player();
    void setMovingLeft(bool);
    void setMovingRight(bool);
    void jump();
    void updateMovement();

private slots:
    void updateAnimation();

private:
    qreal xVelocity = 0;
    qreal yVelocity = 0;
    qreal acceleration = 0.4;
    qreal friction = 0.2;
    qreal gravity = 0.5;
    qreal maxSpeed = 7;
    qreal jumpStrength = -17;

    bool movingLeft = false;
    bool movingRight = false;
    bool onGround = false;

    enum Direction { Left, Right };
    Direction lastDirection = Right;

    QPixmap idleLeftFrame;
    QPixmap idleRightFrame;
    QVector<QPixmap> walkLeftFrames;
    QVector<QPixmap> walkRightFrames;

    int currentFrame = 0;
    QTimer* animationTimer;
};

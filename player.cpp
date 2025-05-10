#include "player.h"
#include <QPixmap>
#include <cmath>
#include <qevent.h>



const int groundhight = 600;

Player::Player() {
    idleLeftFrame.load(":/pictures/player/walkleft.png");
    idleRightFrame.load(":/pictures/player/walkright.png");

    walkLeftFrames = {
        QPixmap(":/pictures/player/walkleft.png").scaled(64, 64),
        QPixmap(":/pictures/player/runleft.png").scaled(64, 64)
    };

    walkRightFrames = {
        QPixmap(":/pictures/player/walkright.png").scaled(64, 64),
        QPixmap(":/pictures/player/runright.png").scaled(64, 64)
    };

    setPixmap(idleRightFrame.scaled(64, 64)); // 初始朝右站立

    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();

    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this, &Player::updateAnimation);
    animationTimer->start(100);
}


void Player::setMovingLeft(bool enable) {
    movingLeft = enable;
    if (enable) lastDirection = Left;
}

void Player::setMovingRight(bool enable) {
    movingRight = enable;
    if (enable) lastDirection = Right;
}

void Player::jump() {
    if (onGround) {
        yVelocity = jumpStrength;
        onGround = false;
    }
}

void Player::updateAnimation() {
    bool nowMoving = (xVelocity != 0);
    if (nowMoving) {
        if (lastDirection == Left) {
            setPixmap(walkLeftFrames[currentFrame]);
        } else {
            setPixmap(walkRightFrames[currentFrame]);
        }
        currentFrame = (currentFrame + 1) % walkLeftFrames.size(); // 同步左右帧数量
    } else {
        setPixmap(lastDirection == Left ? idleLeftFrame : idleRightFrame);
    }
}

void Player::updateMovement() {
    // 水平移动
    if (movingLeft) {
        xVelocity -= acceleration;
    } else if (movingRight) {
        xVelocity += acceleration;
    } else {
        // 摩擦力减速
        if (xVelocity > 0)
            xVelocity -= friction;
        else if (xVelocity < 0)
            xVelocity += friction;

        if (qAbs(xVelocity) < 0.2)
            xVelocity = 0;
    }

    // 限速
    if (xVelocity > maxSpeed) xVelocity = maxSpeed;
    if (xVelocity < -maxSpeed) xVelocity = -maxSpeed;

    // 重力
    yVelocity += gravity;


    // 移动位置
    setX(x() + xVelocity);
    QList<QGraphicsItem*> xCollisions = collidingItems();
    for (QGraphicsItem* item : xCollisions) {
        if (item != this && dynamic_cast<Platform*>(item)) {
            // 回退并停止
            if (xVelocity > 0)
                setX(item->x() - boundingRect().width());  // 从右边撞上
            else
                setX(item->x() + item->boundingRect().width());  // 从左边撞上
            xVelocity = 0;
            break;
        }
    }


    setY(y() + yVelocity);
    QList<QGraphicsItem*> yCollisions = collidingItems();
    bool landed = false;

    for (QGraphicsItem* item : yCollisions) {
        if (item != this && dynamic_cast<Platform*>(item)) {
            if (yVelocity > 0) {
                // 从上落到平台
                setY(item->y() - boundingRect().height());
                onGround = true;
                landed = true;
            } else {
                // 从下撞到平台底部
                setY(item->y() + item->boundingRect().height());
            }
            yVelocity = 0;
            break;
        }
    }

    // 地面检测（防止掉出屏幕）
    if (y() >= groundhight) {
        setY(groundhight);
        yVelocity = 0;
        onGround = true;
        landed = true;
    }

    if (!landed) {
        onGround = false;
    }
}

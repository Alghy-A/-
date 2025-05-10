#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H
#pragma once
#include <QObject>
#include <QEvent>
#include <QKeyEvent>
#include "player.h" // 你自定义的角色类

class PlayerController : public QObject {
    Q_OBJECT
public:
    explicit PlayerController(Player* player);

signals:
    void restartRequested();

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

private:
    Player* player;
};

#endif // PLAYERCONTROLLER_H

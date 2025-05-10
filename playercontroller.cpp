#include "playercontroller.h"

PlayerController::PlayerController(Player* p) : player(p) {}

bool PlayerController::eventFilter(QObject* obj, QEvent* event) {
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_A) player->setMovingLeft(true);
        if (keyEvent->key() == Qt::Key_D) player->setMovingRight(true);
        if (keyEvent->key() == Qt::Key_K) player->jump();
    } else if (event->type() == QEvent::KeyRelease) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_A) player->setMovingLeft(false);
        if (keyEvent->key() == Qt::Key_D) player->setMovingRight(false);
        if (keyEvent->key() == Qt::Key_R) emit restartRequested();
    }
    return false; // 继续传递事件
}

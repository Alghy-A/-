#include "platform.h"
#include <QBrush>
#include<QPen>

Platform::Platform(qreal x, qreal y, qreal width, qreal height) {
    setRect(0, 0, width, height);
    setPos(x, y);
    setBrush(QBrush(Qt::gray));
    setPen(QPen(Qt::NoPen));  // 正确设置无边框
}

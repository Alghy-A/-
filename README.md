# -
南开大学C++大作业
高级语言程序设计大作业报告
基于 Qt 的平台跳跃游戏项目
学生姓名：袁煜杰
学号： 2412303
课程班级：0978
完成时间： 2025年5月6日

一、项目简介
本项目为使用 Qt 框架和 C++ 编程语言开发的一个2D平台跳跃类游戏。游戏参考《超级马里奥》的玩法，玩家可左右移动、跳跃，避开敌人和陷阱，收集金币与道具，最终抵达终点旗帜胜利。

二、主要功能模块及代码解析
1. 主菜单与界面切换
类：MainMenu、game、DeathScreen、WinScreen
主窗口类 game 继承自 QMainWindow，控制整个界面的切换。
MainMenu 提供“开始游戏”按钮，点击后触发 startGame()。
死亡与胜利时分别跳转到 DeathScreen 和 WinScreen，使用 setCentralWidget() 替换中央控件。

// MainMenu 中按钮触发信号
connect(startButton,&QPushButton::clicked,this,&MainMenu::startGameCicked);
// game.cpp 中响应
connect(menuWidget,&MainMenu::startGameClicked,this,&game::startGame）;

3. 游戏场景与元素添加
类：GameScene
继承自 QGraphicsScene，负责添加平台、金币、敌人、陷阱、目标点、道具等。
关键函数：
GameScene::GameScene(QObject* parent) {
    setBackgroundBrush(QPixmap(":/pictures/background/background.jpg");
    addItem(new Platform(...));
    addItem(new Coin(...));
    addItem(new Trap(...));
    addItem(new Enemy(...));
    addItem(new TeleportItem(...));
    addItem(new DoubleJumpItem(...));
    addItem(new Goal());
    setupCoinDisplay();
}

金币 UI 始终显示在右上角：
void GameScene::checkCoinCollision(Player* player, QPointF* cameraPos) {
    ...
    coinText->setPos(cameraPos->x() + 500, cameraPos->y() - 370);  // 跟随摄像机
}

4. 玩家角色控制与物理系统
类：Player, PlayerController
支持左右移动、跳跃、碰撞检测、二段跳、死亡与胜利事件、动画切换、道具触发等。
移动逻辑：
void Player::updateMovement() {
    if (movingLeft) xVelocity -= acceleration;
    else if (movingRight) xVelocity += acceleration;
    else applyFriction();

    yVelocity += gravity;
    handleCollisionX();
    handleCollisionY();
}
动画更新：
void Player::updateAnimation() {
    setPixmap(isMoving ? walkFrame : idleFrame);
}

二段跳：
void Player::jump() {
    if (jumpsRemaining > 0) {
        yVelocity = jumpStrength;
        jumpsRemaining--;
    }
}

传送逻辑：
void Player::teleport() {
    if (!teleportenable || !canTeleport) return;
    setX(x() + (teleportCount % 2 == 0 ? +7960 : -7960));
    teleportCount++;
    canTeleport = false;
    teleportCooldownTimer->start(300);
}

5. 敌人与陷阱
类：Enemy, Trap
敌人为自动移动物体，定期左右反转方向。
陷阱为静态 QGraphicsPixmapItem，角色碰撞即死亡。
void Enemy::move() {
    setX(x() + (movingRight ? speed : -speed));
    if (x() > rightBound || x() < leftBound) movingRight = !movingRight;
}

6. 道具系统与提示
类：Item, TeleportItem, DoubleJumpItem
道具继承自虚基类 Item，提供 applyEffect(Player*) 接口。
示例：双跳道具
void DoubleJumpItem::applyEffect(Player* player) {
    player->enableDoubleJump();
    showFloatingLabel("你获得了二段跳能力，请按 K 使用");
}

7. 游戏胜负逻辑与事件通信
信号与槽机制：
玩家死亡：emit playerDied()，game 响应显示死亡界面
玩家胜利：emit playerWon()，game 响应显示胜利界面
返回主菜单：emit returnToMenuRequested()，由 PlayerController 处理 Esc 键

四、总结与体会
通过本项目我掌握了 Qt 中图形视图框架（Graphics View Framework）的应用，包括：
使用 QGraphicsScene 构建游戏世界
利用 QGraphicsItem 表示游戏角色与对象
运用 QTimer 控制刷新与动画
熟练掌握事件处理机制（键盘控制）
利用继承和信号槽机制实现模块化、交互式逻辑
本项目锻炼了我将面向对象编程、UI 设计与游戏逻辑整合的能力，是一次从零开发完整功能性游戏的宝贵经验。

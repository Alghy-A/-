#include "game.h"
#include "./ui_game.h"

Game::Game(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Game)
{
    ui->setupUi(this);
    scene = new GameScene(this); // 创建游戏场景
    view = new QGraphicsView(scene, this); // 创建视图并加载场景
    view->setFixedSize(1408, 768); // 设置视图大小（窗口尺寸）
    view->setSceneRect(0, 0, 7040, 768); // 设置场景逻辑尺寸（游戏世界）
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // 关闭滚动条
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    this->setFixedSize(view->size()); // 设置主窗口大小与视图一致
    view->show();

    //创建角色
    player = new Player();
    player->setPos(100, 400);       // 设置角色初始位置
    scene->addItem(player);         // 添加到场景中

    //创建控制器
    controller = new PlayerController(player);
    qApp->installEventFilter(controller);



    // 创建计时器
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=]() {
        player->updateMovement();
        view->centerOn(player);
    });
    timer->start(16);  // ~60 FPS

    connect(controller, &PlayerController::restartRequested, this, &Game::restartGame);
}

Game::~Game()
{
    delete ui;
    // 确保定时器和其他动态分配的内存被正确释放
    if (timer) {
        timer->stop();
        delete timer;
    }
    delete player;
    delete controller;
}

void Game::restartGame() {
    player->setPos(100, 400);
}

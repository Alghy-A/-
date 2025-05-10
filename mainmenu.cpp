#include "mainmenu.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QPalette>
#include <QPixmap>

MainMenu::MainMenu(QWidget *parent)
    : QWidget(parent)
{
    this->setFixedSize(1408, 768);

    // 设置背景图片
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(QPixmap(":/pictures/background/mainmenu.jpg"))); // 替换路径为你的实际资源路径
    this->setAutoFillBackground(true);
    this->setPalette(palette);

    // 设置按钮
    startButton = new QPushButton("Start", this);
    startButton->setFixedSize(200, 60);
    startButton->setStyleSheet("font-size: 24px;");

    // 布局
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addStretch();
    layout->addWidget(startButton, 0, Qt::AlignCenter);
    layout->addStretch();

    connect(startButton, &QPushButton::clicked, this, &MainMenu::startGame);
}

MainMenu::~MainMenu()
{

}

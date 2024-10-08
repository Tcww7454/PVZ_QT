#include "pvz.h"
#include "ui_pvz.h"

PVZ::PVZ(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PVZ)
    , scene(new QGraphicsScene(this)) // 在这里初始化 scene
    , mymap(nullptr)  // 初始化为 nullptr
    , toolbar(new ToolBar(":/res/bar5.png")) // 初始化一张图片,修改这里修改工具栏图标
    , cardManager(new CardManager(scene)) // 初始化 CardManager
    , plant(1,"wandou",":/res/Plants/Peashooter/1.gif")
{
    ui->setupUi(this);
    setGraphicsProperty();
    setMapView();
    setToolView();
    addCards();
    scene->addItem(&plant);
    plant.startAnimation();
}

PVZ::~PVZ()
{
    delete mymap; //可选，已经将scene挂到了内存管理的树上了
    delete toolbar; //可选，已经将scene挂到了内存管理的树上了
    delete ui;
}

void PVZ::setGraphicsProperty()
{
    // 固定窗口大小
    this->setFixedSize(1000, 600); // 设置固定窗口大小（根据你的需求）
    // 关闭滚动条
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //将 QGraphicsScene 和 QGraphicsView 关联起来
    ui->graphicsView->setScene(scene);

    //这样就可以通过信号与槽的机制实现卡牌什么的购买拖动了
    //设置各个按钮的不可见状态
    for(int i=1;i<10;i++)
    {
        QString str=QString("btu_%1").arg(i);
        // 使用 findChild() 查找按钮并隐藏
        QPushButton *button = findChild<QPushButton*>(str);
        if (button) {
            button->hide();  // 隐藏按钮
            qDebug() << str << "is hidden.";
        } else {
            qDebug() << str << "not found.";
        }
    }

}

void PVZ::setMapView()
{
    // 创建 QGraphicsScene,改为在初始化列表中
    //scene=new QGraphicsScene(this);

    //创建map对象并添加到场景
    //指定剪切区域
    QRectF cutArea(50,-50,1000,750);

    mymap=new map(":/res/Map/map0.jpg",cutArea);;
    scene->addItem(mymap);//将map添加到场景


    // 设置视图大小
    mymap->setViewSize(ui->graphicsView);
}


void PVZ::setToolView()
{
    // 创建 QGraphicsScene,改为在初始化列表中
    //scene=new QGraphicsScene(this);

    //创建ToolBar对象并添加到场景

    //toolbar=new ToolBar(":/res/Screen/ChooserBackground.png");
    scene->addItem(toolbar);//将map添加到场景

    // 设置视图大小
    //toolbar->setViewSize(ui->graphicsView);
    // 重新绘制以确保显示
    toolbar->update();
}

void PVZ::addCards()
{
    cardManager->addCard("PeaCard",1,100,":/res/Cards/card_1.png");
    cardManager->displayCards();
}

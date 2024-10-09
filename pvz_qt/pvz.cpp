#include "pvz.h"
#include "ui_pvz.h"

PVZ::PVZ(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PVZ)
    , scene(new QGraphicsScene(this)) // 在这里初始化 scene
    , mymap(nullptr)  // 初始化为 nullptr
    , toolbar(new ToolBar(":/res/bar5.png")) // 初始化一张图片,修改这里修改工具栏图标
    , cardManager(new CardManager(scene)) // 初始化 CardManager
    , plantManager(new PlantManager(scene)) // 初始化 PlantManager
    , isCreatingPlant(false) // 初始化植物创建状态为 false
    , currentPlant(nullptr) // 初始化当前植物对象为 nullptr
    , plantsCount(1) // 初始化 plantsCount
{
    ui->setupUi(this);
    setGraphicsProperty();
    setMapView();
    setToolView();
    addCards();
    //addPlants();
    connect(this, &PVZ::plantCardClicked, this, &PVZ::onPlantCardClicked);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
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
    for(int i=2;i<11;i++)
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

    mymap=new map(":/res/bg.jpg",cutArea);;
    scene->addItem(mymap);//将map添加到场景


    // 设置视图大小
    mymap->setViewSize(ui->graphicsView);
}


void PVZ::setToolView()
{
    // 创建 QGraphicsScene,改为在初始化列表中
    //scene=new QGraphicsScene(this);

    //创建ToolBar对象并添加到场景

    toolbar->setOpacity(1.0); // 确保工具栏不透明

    //toolbar=new ToolBar(":/res/Screen/ChooserBackground.png");
    scene->addItem(toolbar);//将map添加到场景

    // 设置视图大小
    //toolbar->setViewSize(ui->graphicsView);
    // 重新绘制以确保显示
    toolbar->update();
}



void PVZ::addCards()
{
    static int p_sum=0;
    cardManager->addCard("PeaCard",1,100,":/res/Cards/card_1.png");
    //cardManager->addCard("SunflowerCard", 2, 50, ":/res/Cards/card_2.png");
    cardManager->displayCards();
    for (int i = 0; i < cardManager->getCardTypes().size(); ++i) {
        CardType type = cardManager->getCardTypes()[i];
        QPushButton* button = findChild<QPushButton*>(QString("btu_%1").arg(i + 1));

        if (button) {
            button->setStyleSheet("background: transparent;"); // 设置透明背景
            connect(button, &QPushButton::pressed, this, [=]() {
                PlantType plantType = cardManager->getPlantType(type);
                emit plantCardClicked(plantType); // 发出信号
                qDebug() << "Button clicked: " << ++p_sum;
            });
            // 隐藏按钮但保留功能
            button->setVisible(true);
        }
    }
}

void PVZ::addPlants()
{
    // 创建一个豌豆射手对象
    //std::shared_ptr<Plant> peashooter = std::make_shared<PeaShooter>(1, "Peashooter", ":/res/Plants/Peashooter/1.gif");

    // 将豌豆射手添加到 PlantManager
    plantManager->createAndAddPlant(PlantType::PeaShooter,1);
}


void PVZ::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if (isCreatingPlant && currentPlant) {
            // 结束植物创建状态并固定植物位置

            QPointF pos = ui->graphicsView->mapToScene(event->pos()); // 获取鼠标在场景中的位置



            currentPlant->setPos(pos); // 设置植物位置
            isCreatingPlant = false; // 结束植物创建状态
            currentPlant = nullptr; // 清空当前植物

            // 恢复鼠标光标
            unsetCursor();
        } else {
            // 处理选择植物卡牌的逻辑（如果需要）
            //setCursor(Qt::BlankCursor);
        }
    }

    // 右键按下以结束植物创建
    // if (event->button() == Qt::RightButton && isCreatingPlant) {
    //     // 可以根据需要结束植物创建
    //     isCreatingPlant = false; // 结束植物创建状态
    //     currentPlant = nullptr; // 清空当前植物
    // }
}

void PVZ::mouseMoveEvent(QMouseEvent *event)
{
    if (isCreatingPlant && currentPlant) {
        QPointF pos = ui->graphicsView->mapToScene(event->pos()); // 获取鼠标在场景中的位置

        // 设置偏移量
        qreal offsetX = -30; // 水平方向的偏移量
        qreal offsetY = -30; // 垂直方向的偏移量
        pos.setX(pos.x() + offsetX);
        pos.setY(pos.y() + offsetY);

        // 定义可拖动区域（例如，限制植物只能在地图区域内移动）
        QRectF validArea(200, 90, 900, 600); // 假设这是可拖动的区域

        // 如果新位置在可拖动区域内，则更新植物位置
        if (validArea.contains(pos)) {
            currentPlant->setPos(pos); // 更新植物位置
            currentPlant->setVisible(true); // 确保植物可见
            ui->graphicsView->viewport()->update(); // 刷新视图
            // 恢复鼠标光标
            unsetCursor();
        }
    }
}





void PVZ::onPlantCardClicked(PlantType plantType) {
    // 只有在没有当前植物时，才创建新的植物对象
    if (!isCreatingPlant && !currentPlant) {
        currentPlant = plantManager->createAndAddPlant(plantType, plantsCount++); // 创建植物

        // 确保植物创建成功
        if (currentPlant) {
            currentPlant->setZValue(10); // 确保植物在工具栏之上
            currentPlant->setOpacity(1.0); // 设置为不透明
            currentPlant->setZValue(10); // 设置植物Z值
            isCreatingPlant = true; // 设置植物创建状态为 true
            currentPlant->setVisible(true); // 确保植物可见

            // 隐藏鼠标光标
            setCursor(Qt::BlankCursor);
        } else {
            qDebug() << "Failed to create plant!";
            isCreatingPlant = false; // 如果创建失败，结束植物创建状态
            currentPlant = nullptr; // 清空当前植物
        }
    }
}

void PVZ::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        // 如果正在创建植物并且当前植物存在
        if (isCreatingPlant && currentPlant) {
            // 在当前鼠标位置设置植物位置
            QPointF pos = ui->graphicsView->mapToScene(event->pos());
            // 设置偏移量
            qreal offsetX = -30; // 水平方向的偏移量
            qreal offsetY = -30; // 垂直方向的偏移量

            // 应用偏移
            pos.setX(pos.x() + offsetX);
            pos.setY(pos.y() + offsetY);


            currentPlant->setPos(pos); // 设置植物位置

            // 结束植物创建状态
            isCreatingPlant = false;
            currentPlant = nullptr; // 清空当前植物
            update();
        }
    }
}

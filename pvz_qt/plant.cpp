#include "plant.h"

Plant::Plant(int id, const QString &name, const QString &gifPath)
    : id(id) , name(name) , movie(std::make_unique<QMovie>(gifPath)),timer(new QTimer(this))
{
    if(movie&& movie->isValid())
    {
        connect(timer, &QTimer::timeout, this, &Plant::updateAnimation);
        timer->start(38);  // 每()毫秒更新一次动画,更改这里可以实现植物抽搐的频率,越小帧率越高
        movie->start();
    }else {
        qWarning() << "Failed to load GIF:" << gifPath; // 检查 GIF 是否有效
    }
}

Plant::~Plant(){
     // 不需要显式 delete，std::unique_ptr 会自动管理内存
    delete timer;//删除定时器
}

QRectF Plant::boundingRect() const {
    // 根据当前 GIF 的尺寸返回边界矩形
    return QRectF(0, 0, movie ? movie->currentPixmap().width() : 0,
                  movie ? movie->currentPixmap().height() : 0);
}

void Plant::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    // 绘制当前帧的 GIF 动画
    UNUSED(option);
    UNUSED(widget);
    // 可选：使用样式选项设置背景或边框
    //painter->setRenderHint(QPainter::Antialiasing); // 启用抗锯齿
    painter->setBrush(Qt::transparent); // 设置透明背景
    painter->setPen(Qt::NoPen); // 不绘制边
    if (movie) {
        //painter->drawPixmap(599, 190, movie->currentPixmap());
        //使用上面那个方法是没办法实现动画的
        QRectF rect = boundingRect();
        painter->drawPixmap(rect.topLeft(), movie->currentPixmap());
    }
}

void Plant::startAnimation() {
    if (movie) {
        movie->start(); // 启动动画
        update(); // 更新视图
    }
}

void Plant::stopAnimation() {
    if (movie) {
        movie->stop(); // 停止动画
        update(); // 更新视图
    }
}

void Plant::updateAnimation() {
    if (movie) {
        movie->jumpToNextFrame(); // 跳到下一个帧
        update(); // 更新视图
    }
}

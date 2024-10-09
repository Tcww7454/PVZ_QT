#include "map.h"

map::map() {
    image=QPixmap(":/res/bg.jpg");
}

map::~map()
{

}

QRectF map::boundingRect() const
{
    return QRectF(0,0,image.width(),image.height());
}

void map::paint(QPainter *painter,const QStyleOptionGraphicsItem*option, QWidget *widget)
{
    UNUSED(option);
    UNUSED(widget);
    if(!image.isNull())
    {
        painter->drawPixmap(0,0,image);
    }
}

void map::setViewSize(QGraphicsView *view)
{
    QSize imageSize=boundingRect().size().toSize();
    view->setFixedSize(imageSize.width(),imageSize.height());
    view->setSceneRect(boundingRect());//设置场景矩形
}

map::map(const QString &imagePath,const QRectF &rect) : cutRect(rect) {
    image = QPixmap(imagePath).copy(rect.toRect()); // 从指定区域剪切图像
}

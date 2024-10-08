#include "toolbar.h"

#include "map.h"

ToolBar::ToolBar() {
    image=QPixmap(":/res/bar.png");
}

ToolBar::~ToolBar()
{

}

QRectF ToolBar::boundingRect() const
{
    return QRectF(0,0,image.width(),image.height());
    //return QRectF(0,0,700,200);
}

void ToolBar::paint(QPainter *painter,const QStyleOptionGraphicsItem*option, QWidget *widget)
{
    UNUSED(option);
    UNUSED(widget);
    if(!image.isNull())
    {
        // 定义缩放因子
        //double scaleFactor = 1.2; // 设置为1.2倍的大小

        // 缩放图像
        QPixmap scaledImage = image.scaled(image.size() , Qt::KeepAspectRatio, Qt::SmoothTransformation);

        painter->drawPixmap(200,0,image);
    }
}

void ToolBar::setViewSize(QGraphicsView *view)
{
    QSize imageSize=boundingRect().size().toSize();
    view->setFixedSize(imageSize.width(),imageSize.height());
    view->setSceneRect(boundingRect());//设置场景矩形
}

ToolBar::ToolBar(const QString &imagePath)  {
    image = QPixmap(imagePath);
}

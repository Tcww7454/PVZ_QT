#ifndef MAP_H
#define MAP_H
#define UNUSED(x) (void)(x)

#include <QGraphicsItem>
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsView>

class map :  public QObject, public QGraphicsItem
{
    Q_OBJECT
    protected:
        QPixmap image;
        QRectF cutRect;//用于指定剪切区域
    public:
        map();
         map(const QString &imagePath, const QRectF &rect); // 添加路径和剪切区域的构造函数
        ~map();
        QRectF boundingRect()const override;
        //设置视图的大小
        void setViewSize(QGraphicsView *view);
        void paint(QPainter *painter,const QStyleOptionGraphicsItem*option, QWidget *widget)override;
};

#endif // MAP_H

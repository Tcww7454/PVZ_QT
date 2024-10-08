#ifndef TOOLBAR_H
#define TOOLBAR_H

#define UNUSED(x) (void)(x)

#include <QGraphicsItem>
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsView>

class ToolBar : public QGraphicsItem
{
public:
protected:
    QPixmap image;
    QRectF cutRect;//用于指定剪切区域
public:
    ToolBar();
    ToolBar(const QString &imagePath); // 添加路径和剪切区域的构造函数
    ~ToolBar();
    QRectF boundingRect()const override;
    //设置视图的大小
    void setViewSize(QGraphicsView *view);
    void paint(QPainter *painter,const QStyleOptionGraphicsItem*option, QWidget *widget)override;
};

#endif // TOOLBAR_H

#ifndef PLANT_H
#define PLANT_H
#define UNUSED(x) (void)(x)
#include <QGraphicsItem>
#include <QObject>
#include <QMovie>
#include <QString>
#include <QPainter>
#include <memory>
#include <QTimer>

class Plant : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Plant(int id, const QString &name, const QString &gifPath);
    virtual ~Plant();

    // 重写 QGraphicsItem 的虚拟函数
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void startAnimation();
    void stopAnimation();

private slots:
    void updateAnimation();  // 定时器槽，用于更新动画

protected:
    int id;
    QString name;
    std::unique_ptr<QMovie> movie;
    QTimer *timer;
};

#endif // PLANT_H

#ifndef CARDS_H
#define CARDS_H

#include <QGraphicsItem>
#include <QObject>
#include<QString>
#include<QPainter>
#define UNUSED(x) (void)(x)

enum class CardType{
    PeaCard=1,
    SunflowerCard=2,
    //其他卡片类型
};

class Cards : public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    Cards();
    Cards(int id, const QString &name, int cost, const QString &imagePath);
    Cards(CardType type ,int id, const QString &name, int cost, const QString &imagePath);

    virtual ~Cards() = default;

    int getId() const ;       // 获取卡牌编号
    QString getName() const ;
    int getCost() const ;
    virtual bool use() = 0;
    QRectF boundingRect()const override;
    void paint(QPainter *painter,const QStyleOptionGraphicsItem*option, QWidget *widget)override;
    virtual CardType getType() const =0;
protected:
    int id;
    QString name;
    CardType type;
    int cost;
    QString imgpath;
    QPixmap image;

private:
    CardType mapNameToType(const QString &name);

};

#endif // CARDS_H

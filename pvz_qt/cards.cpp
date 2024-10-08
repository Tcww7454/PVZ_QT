#include "cards.h"

Cards::Cards() : id(-1), name("null"), cost(-1), imgpath(":/res/Cards/card_1.png")
{
    image = QPixmap(":/res/Cards/card_1.png");//默认就为豌豆的图标了，虽然这个正常情况下是绝对用不到的
}

//使用枚举类型来进行标识
Cards::Cards(CardType type ,int id, const QString &name, int cost, const QString &imagePath)
    : id(id),name(name),  type(type),cost(cost), imgpath(imagePath)
{
    image = QPixmap(imagePath); // 从指定路径加载图像
}

//使用对应的卡牌名来进行标识
Cards::Cards(int id, const QString &name, int cost, const QString &imagePath)
    : id(id),name(name),type(mapNameToType(name)),cost(cost), imgpath(imagePath)
{
    image = QPixmap(imagePath); // 从指定路径加载图像
}

int Cards::getId() const
{
    return id;
}

int Cards::getCost() const{
    return cost;
}

QString Cards::getName() const{
    return name;
}

QRectF Cards::boundingRect() const
{
    return QRectF(0,0,image.width(),image.height());
}

void Cards::paint(QPainter *painter,const QStyleOptionGraphicsItem*option, QWidget *widget)
{
    UNUSED(option);
    UNUSED(widget);
    if(!image.isNull())
    {
        painter->drawPixmap(0,0,image);
    }
}

// 映射函数，将名称转换为枚举类型
CardType Cards::mapNameToType(const QString &name) {
    static const std::unordered_map<QString, CardType> nameToTypeMap = {
        {"PeaCard", CardType::PeaCard},
        {"SunflowerCard", CardType::SunflowerCard},
        // 添加其他卡片名称与枚举的映射
    };

    auto it = nameToTypeMap.find(name);
    return (it != nameToTypeMap.end()) ? it->second : CardType(); // 返回对应的枚举值，默认为未定义
}

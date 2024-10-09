#ifndef CARDMANAGER_H
#define CARDMANAGER_H


#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVector>
#include <QString>
#include <memory>
#include "plantmanager.h"
#include "cards.h"
class CardManager {
public:
    CardManager(QGraphicsScene *scene); // 构造函数，接收一个QGraphicsScene的指针
    void addCard(const QString &name, int id,  int cost, const QString &imagePath); // 添加卡片
    void addCard(CardType type, int id, const QString &name, int cost, const QString &imagePath);
    void displayCards(); // 显示卡片
    PlantType getPlantType(CardType cardType); // 获取植物类型
    std::vector<CardType> getCardTypes(); // 声明 getCardTypes 方法
private:
    QGraphicsScene *scene; // 该类操作的场景
    QVector<std::shared_ptr<Cards>> cards; // 存储卡片的容器，使用智能指针管理卡片的内存
    std::unordered_map<CardType, PlantType> cardToPlantMap; // 建立卡牌和植物间的映射
};

#endif // CARDMANAGER_H

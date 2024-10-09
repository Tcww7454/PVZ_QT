#ifndef PLANTMANAGER_H
#define PLANTMANAGER_H

#include "plant.h"
#include <peashooter.h>
#include <unordered_map>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVector>
#include <QString>
#include <memory>

enum class PlantType {
    PeaShooter,
    SunFlower,
    // 其他植物类型
};


class PlantManager
{
public:
    //初始化主场景
    PlantManager(QGraphicsScene *scene = nullptr);

    // 设置场景
    void setScene(QGraphicsScene *newScene);

    // 添加植物到场景
    void addPlant(int id, std::shared_ptr<Plant> plant);

    // 根据id移除植物
    void removePlant(int id);

    // 获取植物
    std::shared_ptr<Plant> getPlant(int id) const;

    // 清空所有植物
    void clearAllPlants();

    //根据名称来添加植物
    std::shared_ptr<Plant> createAndAddPlant(PlantType type,int id);

private:
    QGraphicsScene *scene; // 该类操作的场景
    std::unordered_map<int , std::shared_ptr<Plant>> plants;
};

#endif // PLANTMANAGER_H

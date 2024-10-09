#include "plantmanager.h"

PlantManager::PlantManager(QGraphicsScene *scene )
    :scene(scene){}

void PlantManager::setScene (QGraphicsScene *newScene)
{
    scene=newScene;
}

void PlantManager::addPlant(int id, std::shared_ptr<Plant> plant)
{
    plants[id]=plant;
    scene->addItem(plant.get());
}

void PlantManager::removePlant(int id)
{
    if(plants.find(id)!=plants.end())
    {
        scene->removeItem(plants[id].get());
        plants.erase(id);
    }
}

std::shared_ptr<Plant> PlantManager::getPlant(int id) const
{
    auto it = plants.find(id);
    if (it != plants.end()) {
        return it->second;
    }
    return nullptr;
}

void PlantManager::clearAllPlants()
{
    for (auto& pair : plants) {
        scene->removeItem(pair.second.get());  // 从场景中移除每个植物
    }
    plants.clear();  // 清空管理器中的植物
}

void PlantManager::createAndAddPlant(PlantType type, int id)
{
    std::shared_ptr<Plant> plant = nullptr;

    // 根据传入的植物类型创建不同的植物
    switch (type) {
    case PlantType::PeaShooter:
        plant = std::make_shared<PeaShooter>(id, "PeaShooter", ":/res/Plants/Peashooter/1.gif");
        break;

    // case PlantType::Sunflower:
    //     plant = std::make_shared<Sunflower>(id, "Sunflower", "path_to_sunflower_gif");
    //     break;

        // 其他植物的创建逻辑
    default:
        break;
    }

    // 如果植物创建成功，将其添加到管理器和场景
    if (plant) {
        addPlant(id, plant);
    }
}


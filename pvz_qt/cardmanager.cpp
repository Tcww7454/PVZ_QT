#include "cardmanager.h"
#include "peacard.h"
CardManager::CardManager(QGraphicsScene *scene) : scene(scene)
{
    // 初始化 CardType 到 PlantType 的映射
    cardToPlantMap[CardType::PeaCard] = PlantType::PeaShooter;
    cardToPlantMap[CardType::SunflowerCard] = PlantType::SunFlower;
    // 其他映射关系之后添加
}

//使用shared_ptr实现智能指针的可复制
void CardManager::addCard(const QString &name, int id, int cost, const QString &imagePath ) {
    std::shared_ptr<Cards> card;

    // 根据名称创建对应的卡片对象
    if (name == "PeaCard") {
        card = std::make_shared<PeaCard>(id, name, cost, imagePath);
    } /*else if (name == "SunflowerCard") {
        card = std::make_shared<SunflowerCard>(id, name, cost, imagePath);
    }*/

    if (card&&scene) {
        cards.push_back(card);  // 共享智能指针可以正常复制
        scene->addItem(card.get());  // 将卡片添加到场景中
        //cardTypes.push_back(type);
    }
}

// 使用枚举类型进行标识的重载函数
void CardManager::addCard(CardType type, int id, const QString &name, int cost, const QString &imagePath) {
    std::shared_ptr<Cards> card;

    // 根据枚举类型创建对应的卡片对象
    if (type == CardType::PeaCard) {
        card = std::make_shared<PeaCard>(type, id, name, cost, imagePath);
    }
    // 可以继续添加其他卡片类型
    /* else if (type == CardType::SunflowerCard) {
        card = std::make_shared<SunflowerCard>(type, id, name, cost, imagePath);
    } */

    if (card && scene) {
        cards.push_back(card);  // 共享智能指针可以正常复制
        scene->addItem(card.get());  // 将卡片添加到场景中
    }
    // 使用映射可获取植物类型
    //PlantType plantType = getPlantType(type);
}

void CardManager::displayCards() {
    for (const auto &card : cards) {
        card->setPos(285, 5); // 设置位置
    }
}

PlantType CardManager::getPlantType(CardType cardType) {
    auto it = cardToPlantMap.find(cardType);
    if (it != cardToPlantMap.end()) {
        return it->second; // 返回对应的 PlantType
    }
    throw std::runtime_error("Invalid CardType");
}

std::vector<CardType> CardManager::getCardTypes() {
    std::vector<CardType> cardTypes; // 创建一个 vector 容器来存储卡牌类型
    for (const auto &card : cards) { // 遍历存储卡牌的容器
        cardTypes.push_back(card->getType()); // 添加卡牌类型到列表
    }
    return cardTypes; // 返回包含所有卡牌类型的容器
}

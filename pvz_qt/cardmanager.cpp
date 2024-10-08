#include "cardmanager.h"

CardManager::CardManager(QGraphicsScene *scene) : scene(scene) {}

//使用shared_ptr实现智能指针的可复制
void CardManager::addCard(const QString &name, int id, int cost, const QString &imagePath) {
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
}

void CardManager::displayCards() {
    for (const auto &card : cards) {
        card->setPos(285, 5); // 设置位置
    }
}


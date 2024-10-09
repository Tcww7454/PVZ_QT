#ifndef PVZ_H
#define PVZ_H

#include"map.h"
#include"toolbar.h"
#include <QWidget>
#include<QString>
#include<QPushButton>
#include<peacard.h>
#include<cardmanager.h>
#include<plantmanager.h>
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class PVZ;
}
QT_END_NAMESPACE

class PVZ : public QWidget
{
    Q_OBJECT

public:
    PVZ(QWidget *parent = nullptr);
    ~PVZ();
    void setMapView();
    void setToolView();
    void setGraphicsProperty();
    void setPlants();
    void addCards();
    void addPlants();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void onPlantCardClicked(PlantType plantType);//测试
    void mouseReleaseEvent(QMouseEvent *event);
signals:
    void plantCardClicked(PlantType plantType);

private:
    Ui::PVZ *ui;
    QGraphicsScene *scene;
    map *mymap;
    ToolBar *toolbar;
    CardManager*cardManager;
    PlantManager *plantManager;
    bool isCreatingPlant = false; // 用于指示是否正在创建植物
    std::shared_ptr<Plant> currentPlant; // 当前正在创建的植物
    int plantsCount; // 用于生成植物 ID
};
#endif // PVZ_H

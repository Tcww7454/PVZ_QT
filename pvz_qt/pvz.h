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
private:
    Ui::PVZ *ui;
    QGraphicsScene *scene;
    map *mymap;
    ToolBar *toolbar;
    CardManager*cardManager;
    PlantManager *plantManager;
    //Plant plant;

};
#endif // PVZ_H

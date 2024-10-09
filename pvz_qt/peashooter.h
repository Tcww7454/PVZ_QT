#ifndef PEASHOOTER_H
#define PEASHOOTER_H

#include "plant.h"

class PeaShooter : public Plant
{
    Q_OBJECT
public:
    PeaShooter(int id, const QString &name="PeaShooter", const QString &gifPath=":/res/Plants/Peashooter/1.gif");
    void specialAbility() override;
};

#endif // PEASHOOTER_H

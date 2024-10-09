#include "peashooter.h"

PeaShooter::PeaShooter(int id, const QString &name, const QString &gifPath)
    : Plant(id, name, gifPath)
{
    setVisible(true); // 确保植物可见
}

void PeaShooter::specialAbility()
{

}

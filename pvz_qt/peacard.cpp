#include "peacard.h"

PeaCard::PeaCard() {}
PeaCard::PeaCard(CardType type,int id, const QString &name, int cost, const QString &imagePath)
    :Cards(type,id,name,cost,imagePath){}

PeaCard::PeaCard(int id, const QString &name, int cost, const QString &imagePath)
    :Cards(id,name,cost,imagePath){}

PeaCard::~PeaCard(){}

QRectF PeaCard::boundingRect() const
{
    return QRectF(0,0,image.width(),image.height());
}

void PeaCard::paint(QPainter *painter,const QStyleOptionGraphicsItem*option, QWidget *widget)
{
    UNUSED(option);
    UNUSED(widget);
    if(!image.isNull())
    {
        painter->drawPixmap(0,0,image);
    }
}

bool PeaCard::use()
{
    return false;
}

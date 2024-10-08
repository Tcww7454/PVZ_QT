#ifndef PEACARD_H
#define PEACARD_H

#include "cards.h"

class PeaCard : public Cards
{
public:
    PeaCard();
    PeaCard( CardType type,int id=1, const QString &name="PeaCard", int cost=100, const QString &imagePath=":/res/Cards/card_1.png");
    PeaCard(int id, const QString &name, int cost, const QString &imagePath);
    ~PeaCard();
    QRectF boundingRect()const override;
    void paint(QPainter *painter,const QStyleOptionGraphicsItem*option, QWidget *widget)override;
    bool use()override;
};

#endif // PEACARD_H

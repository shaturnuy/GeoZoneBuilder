#pragma once

#include "AbstractPointItem.h"

class ConvexPointItem : public AbstractPointItem
{
public:
    ConvexPointItem(AbstractPoint* point, AbstractPointItem* parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    const double mk_radius = 8.0;
    const QColor mk_color = Qt::red;
};

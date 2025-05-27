#include "MinimumAreaZoneItem.h"

#include <QPainter>
#include <QPainterPath>


void MinimumAreaZoneItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QColor color(Qt::cyan);
    painter->setPen(QPen(color, 2));

    color.setAlpha(80);
    painter->setBrush(color);

    AbstractZoneItem::paint(painter, option, widget);
}

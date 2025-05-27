#include "ConvexZoneItem.h"

#include <QPainter>
#include <QPainterPath>


void ConvexZoneItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QColor color(Qt::red);
    painter->setPen(QPen(color, 2));

    color.setAlpha(80);
    painter->setBrush(color);

    AbstractZoneItem::paint(painter, option, widget);
}

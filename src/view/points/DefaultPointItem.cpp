#include "DefaultPointItem.h"
#include <QPainter>

constexpr double k_penWidth = 2.0;

DefaultPointItem::DefaultPointItem(AbstractPoint* point, AbstractPointItem* parent) :
    AbstractPointItem{point, parent}
{
    setFlag(MapGraphicsObjectFlag::ObjectIsMovable);
    setFlag(MapGraphicsObjectFlag::ObjectIsFocusable);

    setOpacity(0.7);
}

QRectF DefaultPointItem::boundingRect() const
{
    constexpr double k_penWidthOffset = k_penWidth / 2;
    return QRectF(-mk_radius - k_penWidthOffset, -mk_radius - k_penWidthOffset,
                  2 * (mk_radius + k_penWidthOffset), 2 * (mk_radius + k_penWidthOffset));
}

void DefaultPointItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(mk_color);
    painter->setPen(QPen(QBrush(Qt::black), k_penWidth));
    painter->drawEllipse(QPointF(0, 0), mk_radius, mk_radius);
}

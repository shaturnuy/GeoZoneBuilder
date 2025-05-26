#include "MinimumAreaPointItem.h"
#include <QPainter>

constexpr double k_penWidth = 2.0;

MinimumAreaPointItem::MinimumAreaPointItem(AbstractPoint* point, AbstractPointItem* parent) :
    AbstractPointItem{point, parent}
{
    setFlag(MapGraphicsObjectFlag::ObjectIsMovable);
    setFlag(MapGraphicsObjectFlag::ObjectIsFocusable);

    setOpacity(0.7);
}

QRectF MinimumAreaPointItem::boundingRect() const
{
    constexpr double k_penWidthOffset = k_penWidth / 2;
    return QRectF(-mk_width - k_penWidthOffset, -mk_width - k_penWidthOffset,
                  2 * (mk_width + k_penWidthOffset), 2 * (mk_width + k_penWidthOffset));
}

void MinimumAreaPointItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(mk_color);
    painter->setPen(QPen(QBrush(Qt::black), k_penWidth));
    painter->drawRect(-mk_width / 2, -mk_width / 2, mk_width, mk_width);
}

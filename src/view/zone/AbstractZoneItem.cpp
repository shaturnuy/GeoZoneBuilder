#include "AbstractZoneItem.h"

#include <QPainter>
#include <QPainterPath>

#include "3rdparty/MapGraphics/MapGraphics/guts/Conversions.h"

AbstractZoneItem::~AbstractZoneItem() = default;

AbstractZoneItem::AbstractZoneItem(MapGraphicsObject* parent) :
    MapGraphicsObject{false, parent}
{
    setFlag(MapGraphicsObject::ObjectIsMovable, false);
    setFlag(MapGraphicsObject::ObjectIsSelectable,false);
    setFlag(MapGraphicsObject::ObjectIsFocusable, false);
}

void AbstractZoneItem::setGeoPolygon(const QPolygonF &geoPolygon)
{
    if (geoPolygon == m_polygon)
        return;

    m_polygon = geoPolygon;
    setPos(m_polygon.boundingRect().center());
}

QRectF AbstractZoneItem::boundingRect() const
{
    if (m_polygon.isEmpty())
        return QRectF();

    QRectF latLonRect = m_polygon.boundingRect();
    QPointF latLonCenter = latLonRect.center();
    Position latLonCenterPos(latLonCenter, 0.0);
    Position topLeftPos(latLonRect.topLeft(), 0.0);
    Position bottomRightPos(latLonRect.bottomRight(), 0.0);

    QPointF topLeftENU = Conversions::lla2enu(topLeftPos, latLonCenterPos).toPointF();
    QPointF bottomRightENU = Conversions::lla2enu(bottomRightPos, latLonCenterPos).toPointF();

    return QRectF(topLeftENU, bottomRightENU);
}

void AbstractZoneItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);


    QPolygonF enuPoly;

    const Position latLonCenterPos(m_polygon.boundingRect().center(), 0);
    for(const QPointF &latLon : std::as_const(m_polygon))
    {
        Position latLonPos(latLon, 0.0);
        QPointF enu = Conversions::lla2enu(latLonPos, latLonCenterPos).toPointF();
        enuPoly << enu;
    }

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->drawPolygon(enuPoly);
}

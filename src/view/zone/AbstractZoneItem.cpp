#include "AbstractZoneItem.h"

#include <QPainter>
#include <QPainterPath>

#include "3rdparty/MapGraphics/MapGraphics/guts/Conversions.h"

AbstractZoneItem::AbstractZoneItem(QPolygonF geoPoly, MapGraphicsObject* parent)
    : MapGraphicsObject(false, parent)
{
    setFlag(MapGraphicsObject::ObjectIsMovable);
    setFlag(MapGraphicsObject::ObjectIsSelectable,false);
    setFlag(MapGraphicsObject::ObjectIsFocusable);
    setGeoPoly(geoPoly);
}

void AbstractZoneItem::setGeoPoly(const QPolygonF &newPoly)
{
    if (newPoly == _geoPoly)
        return;

    _geoPoly = newPoly;

    this->setPos(newPoly.boundingRect().center());
}

void AbstractZoneItem::setPoints(const QVector<AbstractPoint*> &points)
{
    if (m_points == points)
        return;

    m_points = points;

    _geoPoly.clear();
    for (auto *point : m_points)
        _geoPoly << QPointF(point->latitude(), point->longitude());
    setGeoPoly(_geoPoly);

    // setPos(_geoPoly.boundingRect().center());

    // this->redrawRequested();
}

QVector<AbstractPoint*> AbstractZoneItem::points() const
{
    return m_points;
}

QRectF AbstractZoneItem::boundingRect() const
{
    if (_geoPoly.isEmpty())
        return QRectF();

    QRectF latLonRect = _geoPoly.boundingRect();
    QPointF latLonCenter = latLonRect.center();
    Position latLonCenterPos(latLonCenter, 0.0);
    Position topLeftPos(latLonRect.topLeft(), 0.0);
    Position bottomRightPos(latLonRect.bottomRight(), 0.0);

    QPointF topLeftENU = Conversions::lla2enu(topLeftPos, latLonCenterPos).toPointF();
    QPointF bottomRightENU = Conversions::lla2enu(bottomRightPos, latLonCenterPos).toPointF();

    return QRectF(topLeftENU, bottomRightENU);
}

void AbstractZoneItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/)
{
    if (_geoPoly.size() < 3)
        return;

    painter->setRenderHint(QPainter::Antialiasing, true);

    QPainterPath path;

    QPointF latLonCenter = _geoPoly.boundingRect().center();
    Position centerPos(latLonCenter, 0.0);

    // Переводим каждую точку в ENU и добавляем в path
    for (int i = 0; i < _geoPoly.size(); ++i)
    {
        Position pos(_geoPoly.at(i), 0.0);
        QPointF enu = Conversions::lla2enu(pos, centerPos).toPointF();

        if (i == 0)
            path.moveTo(enu);
        else
            path.lineTo(enu);
    }

    path.closeSubpath();

    painter->setBrush(QColor(255, 0, 0, 80));
    painter->setPen(QPen(Qt::red, 2));
    painter->drawPath(path);
}

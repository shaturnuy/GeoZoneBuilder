#include "ZoneController.h"

ZoneController::ZoneController(ZoneType type, AbstractZoneBuilder *builder, QObject *parent) :
    QObject{parent},
    m_type{type},
    m_builder{builder},
    m_item{new AbstractZoneItem(QPolygonF())}
{
}

void ZoneController::updateZone(const QVector<AbstractPoint*> points)
{
    if (!m_builder)
        return;

    m_builder->buildZone(points);
    m_item->setPoints(points);

    QPolygonF poly;
    for (auto point : points)
        poly << QPointF(point->longitude(), point->latitude());
    m_item->setGeoPoly(poly);
}

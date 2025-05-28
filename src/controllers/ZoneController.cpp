#include "ZoneController.h"

#include "view/ZoneBuilderFactory.hpp"
#include "view/ZoneItemFactory.hpp"

ZoneController::ZoneController(ZoneType type, QObject *parent) :
    QObject{parent},
    m_type{type},
    m_builder{ZoneBuilderFactory::create(type)},
    m_item{ZoneItemFactory::create(type)}
{
}

void ZoneController::updateZone(QVector<QPointF> &&points)
{
    if (!m_builder)
        return;

    m_item->setGeoPolygon(m_builder->buildZone(std::move(points)));
}

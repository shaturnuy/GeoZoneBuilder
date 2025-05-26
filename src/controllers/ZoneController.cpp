#include "ZoneController.h"

ZoneController::ZoneController(ZoneType type, AbstractZoneBuilder *builder, QObject *parent) :
    QObject{parent},
    m_type{type},
    m_builder{builder}
{
    // updateZone(const std::vector<AbstractPoint*> points);
}

void ZoneController::updateZone(const std::vector<AbstractPoint*> points)
{
    // m_builder->buildZone(points);
}

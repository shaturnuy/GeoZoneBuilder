#include "ZoneController.h"

ZoneController::ZoneController(AbstractZoneBuilder *builder, QObject *parent) :
    QObject{parent},
    m_builder{builder}
{
    // updateZone(const std::vector<AbstractPoint*> points);
}

void ZoneController::updateZone(const std::vector<AbstractPoint*> points)
{
    // m_builder->buildZone(points);
}

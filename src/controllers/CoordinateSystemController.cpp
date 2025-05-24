#include "CoordinateSystemController.h"

CoordinateSystemController& CoordinateSystemController::instance()
{
    static CoordinateSystemController instance;
    return instance;
}

void CoordinateSystemController::setSystem(CoordinateSystem system)
{
    if (m_system != system)
    {
        m_system = system;
        emit coordinateSystemChanged(system);
    }
}

QString CoordinateSystemController::systemString() const
{
    switch (m_system)
    {
    case CoordinateSystem::WGS84:   return "WGS-84";
    case CoordinateSystem::SK42:    return "СК-84";
    default:                        return QString{};
    }
}

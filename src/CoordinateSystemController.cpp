#include "CoordinateSystemController.h"

CoordinateSystemController::CoordinateSystemController() :
    m_system{CoordinateSystem::WGS84}
{
}

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
    QString string{};

    switch (m_system)
    {
    case CoordinateSystem::WGS84:   string = "WGS-84";  break;
    case CoordinateSystem::SK42:    string = "СК-84";   break;
    }

    return string;
}

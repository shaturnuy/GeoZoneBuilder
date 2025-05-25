#include "AbstractPoint.h"

void AbstractPoint::setPosition(double latitude, double longitude)
{
    if (qFuzzyCompare(m_latitude, latitude) && qFuzzyCompare(m_longitude, longitude))
        return;

    m_latitude = latitude;
    m_longitude = longitude;

    emit posChanged();
}

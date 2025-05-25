#include "AbstractPointItem.h"

AbstractPointItem::AbstractPointItem(const AbstractPoint *point, MapGraphicsObject *parent) :
    MapGraphicsObject{true, parent},
    m_point{point}
{
    setLatitude(point->latitude());
    setLongitude(point->longitude());
}

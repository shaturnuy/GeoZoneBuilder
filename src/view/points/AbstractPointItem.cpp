#include "AbstractPointItem.h"

AbstractPointItem::AbstractPointItem(AbstractPoint *point, MapGraphicsObject *parent) :
    MapGraphicsObject{true, parent},
    m_point{point}
{
    setLatitude(point->latitude());
    setLongitude(point->longitude());

    connect(this, &MapGraphicsObject::posChanged, this, &AbstractPointItem::onPosChanged);
}

void AbstractPointItem::onPosChanged()
{
    const double lat = this->pos().y();
    const double lon = this->pos().x();

    m_point->setPosition(lat, lon);
}

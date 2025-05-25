#include "AbstractPointItem.h"
#include <QKeyEvent>

AbstractPointItem::AbstractPointItem(AbstractPoint *point, MapGraphicsObject *parent) :
    MapGraphicsObject{true, parent},
    m_point{point}
{
    setLatitude(point->latitude());
    setLongitude(point->longitude());

    connect(this, &MapGraphicsObject::posChanged, this, &AbstractPointItem::onPosChanged);
}

void AbstractPointItem::keyReleaseEvent(QKeyEvent *event)
{
    if (event->matches(QKeySequence::Delete))
    {
        emit deleteFromMap(this);
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void AbstractPointItem::onPosChanged()
{
    const double lat = this->pos().y();
    const double lon = this->pos().x();

    m_point->setPosition(lat, lon);
}

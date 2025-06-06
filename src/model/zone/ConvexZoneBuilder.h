#pragma once

#include "AbstractZoneBuilder.hpp"

class ConvexZoneBuilder : public AbstractZoneBuilder
{
public:
    ConvexZoneBuilder() : AbstractZoneBuilder() {};

    QPolygonF buildZone(QVector<QPointF> &&points) override;
};

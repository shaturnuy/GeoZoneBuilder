#pragma once

#include <QPolygonF>

#include "model/point/AbstractPoint.h"

class AbstractZoneBuilder
{
public:
    explicit AbstractZoneBuilder() {}
    virtual ~AbstractZoneBuilder() = default;

    virtual QPolygonF buildZone(const std::vector<AbstractPoint*>& points) = 0;
};

#pragma once

#include <QPolygonF>

#include "global.hpp"
#include "model/point/AbstractPoint.h"

class AbstractZoneBuilder
{
public:
    explicit AbstractZoneBuilder(ZoneType type) : m_type{type} {}
    virtual ~AbstractZoneBuilder() = default;

    virtual QPolygonF buildZone(const std::vector<AbstractPoint*>& points) = 0;
    inline ZoneType type() const { return m_type; }

private:
    ZoneType m_type;
};

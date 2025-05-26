#pragma once

#include "AbstractZoneBuilder.hpp"

class ConvexZoneBuilder : public AbstractZoneBuilder
{
public:
    ConvexZoneBuilder() : AbstractZoneBuilder() {};

    QPolygonF buildZone(const std::vector<AbstractPoint*> &points) override;
};

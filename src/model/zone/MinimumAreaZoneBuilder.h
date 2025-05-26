#pragma once

#include "AbstractZoneBuilder.hpp"

class MinimumAreaZoneBuilder : public AbstractZoneBuilder
{
public:
    MinimumAreaZoneBuilder() = default;

    QPolygonF buildZone(const std::vector<AbstractPoint*> &points) override;
};

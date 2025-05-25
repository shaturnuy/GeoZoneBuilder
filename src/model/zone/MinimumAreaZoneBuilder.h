#pragma once

#include "IZoneBuilder.hpp"

class MinimumAreaZoneBuilder : public IZoneBuilder
{
public:
    MinimumAreaZoneBuilder() = default;

    QPolygonF buildZone(const QVector<AbstractPoint*> &points) override;
};

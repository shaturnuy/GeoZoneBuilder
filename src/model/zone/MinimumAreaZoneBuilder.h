#pragma once

#include "AbstractZoneBuilder.hpp"

class MinimumAreaZoneBuilder : public AbstractZoneBuilder
{
public:
    MinimumAreaZoneBuilder() = default;

    QPolygonF buildZone(QVector<QPointF> &&points) override;
};

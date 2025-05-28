#pragma once

#include <QPolygonF>

class AbstractZoneBuilder
{
public:
    explicit AbstractZoneBuilder() {}
    virtual ~AbstractZoneBuilder() = default;

    virtual QPolygonF buildZone(QVector<QPointF> &&points) = 0;
};

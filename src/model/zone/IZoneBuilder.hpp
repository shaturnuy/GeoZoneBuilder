#pragma once

#include <QPolygonF>
#include "model/points/AbstractPoint.h"

class IZoneBuilder
{
public:
    enum class Type
    {
        Default
    };

public:
    IZoneBuilder(Type type = Type::Default) : m_type{type} {}
    virtual ~IZoneBuilder() = default;

    virtual QPolygonF buildZone(const QVector<AbstractPoint*>& points) = 0;
    inline Type type() const { return m_type; }

private:
    Type m_type;
};

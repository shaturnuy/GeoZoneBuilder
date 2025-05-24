#pragma once

#include "model/points/AbstractPoint.hpp"

class DefaultPoint : public AbstractPoint
{
public:
    DefaultPoint(double lat = 0.0, double lon = 0.0) : AbstractPoint(lat, lon, Type::Type1) {}

    inline QString typeName() const override { return "Тип 1"; }
};

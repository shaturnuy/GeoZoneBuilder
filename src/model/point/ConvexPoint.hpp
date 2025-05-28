#pragma once

#include "AbstractPoint.h"

class ConvexPoint : public AbstractPoint
{
public:
    ConvexPoint(double latitude = 0.0, double longitude = 0.0) :
        AbstractPoint(ZoneType::Convex, latitude, longitude) {}

    ~ConvexPoint() {};
};

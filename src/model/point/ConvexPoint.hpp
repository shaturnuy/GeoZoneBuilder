#pragma once

#include "AbstractPoint.h"

class ConvexPoint : public AbstractPoint
{
public:
    ConvexPoint(double latitude, double longitude) :
        AbstractPoint(ZoneType::Convex, latitude, longitude) {}

    ~ConvexPoint() {};
};

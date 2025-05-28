#pragma once

#include "AbstractPoint.h"

class MinimumAreaPoint : public AbstractPoint
{
public:
    MinimumAreaPoint(double latitude = 0.0, double longitude = 0.0) :
        AbstractPoint(ZoneType::MinimumArea, latitude, longitude) {}

    ~MinimumAreaPoint() {};
};

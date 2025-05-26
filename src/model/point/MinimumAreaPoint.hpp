#pragma once

#include "AbstractPoint.h"

class MinimumAreaPoint : public AbstractPoint
{
public:
    MinimumAreaPoint(double latitude, double longitude) :
        AbstractPoint(ZoneType::MinimumArea, latitude, longitude) {}

    ~MinimumAreaPoint() {};
};

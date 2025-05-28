#pragma once

#include "global.hpp"
#include <iostream>

#include "model/point/AbstractPoint.h"
#include "model/point/ConvexPoint.hpp"
#include "model/point/MinimumAreaPoint.hpp"


class PointFactory
{
public:
    static AbstractPoint* create(ZoneType type)
    {
        switch (type)
        {
        case ZoneType::Convex:
        {
            return new ConvexPoint;
        }
        case ZoneType::MinimumArea:
        {
            return new MinimumAreaPoint;
        }
        default: // УловительОшибок3000
        {
            std::cerr << __FILE__ << ':' << __LINE__ << ' ' << "Don't forget to add a new Point" << std::endl;
            std::terminate();
        }
        }
    }
};

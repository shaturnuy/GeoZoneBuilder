#pragma once

#include <iostream>

#include "model/point/ConvexPoint.hpp"
#include "model/point/MinimumAreaPoint.hpp"

#include "view/point/AbstractPointItem.h"
#include "view/point/ConvexPointItem.h"
#include "view/point/MinimumAreaPointItem.h"

class PointItemFactory
{
public:
    static AbstractPointItem* create(ZoneType type, AbstractPoint* point)
    {
        switch (type)
        {
        case ZoneType::Convex:
        {
            return new ConvexPointItem(point);
        }
        case ZoneType::MinimumArea:
        {
            return new MinimumAreaPointItem(point);
        }
        default: // УловительОшибок3000
        {
            std::cerr << __FILE__ << ':' << __LINE__ << ' ' << "Don't forget to add a new PointItem" << std::endl;
            std::terminate();
        }
        }
    }
};

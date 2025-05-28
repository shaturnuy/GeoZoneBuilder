#pragma once

#include "global.hpp"
#include <iostream>

#include "view/zone/AbstractZoneItem.h"
#include "view/zone/ConvexZoneItem.h"
#include "view/zone/MinimumAreaZoneItem.h"

class ZoneItemFactory
{
public:
    static AbstractZoneItem* create(ZoneType type)
    {
        switch (type)
        {
        case ZoneType::Convex:
        {
            return new ConvexZoneItem;
        }
        case ZoneType::MinimumArea:
        {
            return new MinimumAreaZoneItem;
        }
        default: // УловительОшибок3000
        {
            std::cerr << __FILE__ << ':' << __LINE__ << ' ' << "Don't forget to add a new ZoneItem" << std::endl;
            std::terminate();
        }
        }
    }
};

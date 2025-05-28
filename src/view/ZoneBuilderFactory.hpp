#pragma once

#include <iostream>

#include "global.hpp"
#include "model/zone/AbstractZoneBuilder.hpp"
#include "model/zone/ConvexZoneBuilder.h"
#include "model/zone/MinimumAreaZoneBuilder.h"

class ZoneBuilderFactory
{
public:
    static AbstractZoneBuilder* create(ZoneType type)
    {
        switch (type)
        {
        case ZoneType::Convex:
        {
            return new ConvexZoneBuilder;
        }
        case ZoneType::MinimumArea:
        {
            return new MinimumAreaZoneBuilder;
        }
        default: // УловительОшибок3000
        {
            std::cerr << __FILE__ << ':' << __LINE__ << ' ' << "Don't forget to add a new ZoneBuilder" << std::endl;
            std::terminate();
        }
        }
    }
};

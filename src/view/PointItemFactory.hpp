#pragma once

#include "model/point/ConvexPoint.hpp"
#include "model/point/MinimumAreaPoint.hpp"

#include "view/point/AbstractPointItem.h"
#include "view/point/ConvexPointItem.h"
#include "view/point/MinimumAreaPointItem.h"

class PointItemFactory
{
public:
    static AbstractPointItem* create(AbstractPoint* point)
    {
        if (!point)
            return nullptr;

        if (auto pointCast = dynamic_cast<ConvexPoint*>(point))
            return new ConvexPointItem(pointCast);
        else if (auto pointCast = dynamic_cast<MinimumAreaPoint*>(point))
            return new MinimumAreaPointItem(pointCast);

        return nullptr;
    }
};

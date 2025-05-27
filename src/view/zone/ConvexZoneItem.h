#pragma once

#include "AbstractZoneItem.h"

class ConvexZoneItem : public AbstractZoneItem
{
public:
    ConvexZoneItem() : AbstractZoneItem() {}
    ~ConvexZoneItem() {}

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};

#pragma once

#include "AbstractZoneItem.h"

class MinimumAreaZoneItem : public AbstractZoneItem
{
public:
    MinimumAreaZoneItem() : AbstractZoneItem() {}
    ~MinimumAreaZoneItem() {}

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};

#pragma once

#include "AbstractPointItem.h"

class MinimumAreaPointItem : public AbstractPointItem
{
public:
    MinimumAreaPointItem(AbstractPoint* point, AbstractPointItem* parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    const double mk_width = 14.0;
    const QColor mk_color = Qt::GlobalColor::blue;
};

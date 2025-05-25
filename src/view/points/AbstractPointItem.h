#pragma once

#include <QGraphicsItem>
#include "model/points/AbstractPoint.h"
#include "MapGraphicsObject.h"

class AbstractPointItem : public MapGraphicsObject
{
public:
    explicit AbstractPointItem(AbstractPoint *point, MapGraphicsObject *parent = nullptr);
    virtual ~AbstractPointItem() = default;

    inline const AbstractPoint* point() const { return m_point; }

    virtual QRectF boundingRect() const = 0;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) = 0;

protected slots:
    void onPosChanged();

protected:
    AbstractPoint* m_point;
};

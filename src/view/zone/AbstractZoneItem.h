#pragma once

#include <QVector>
#include <QPointF>

#include "MapGraphicsObject.h"


class AbstractZoneItem : public MapGraphicsObject
{
    Q_OBJECT

public:
    explicit AbstractZoneItem(MapGraphicsObject* parent = nullptr);
    virtual ~AbstractZoneItem() = 0;

    void setGeoPolygon(const QPolygonF &geoPolygon);

    QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    QPolygonF m_polygon;
};

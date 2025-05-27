#pragma once

#include <QVector>
#include <QPointF>

#include "MapGraphicsObject.h"
#include "model/point/AbstractPoint.h"


class AbstractZoneItem : public MapGraphicsObject
{
    Q_OBJECT

public:
    explicit AbstractZoneItem(QPolygonF geoPoly, MapGraphicsObject* parent = nullptr);

    void setPoints(const QVector<AbstractPoint*> &points);
    void setGeoPoly(const QPolygonF &newPoly);
    QVector<AbstractPoint*> points() const;

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

private:
    QVector<AbstractPoint*> m_points;
    QPolygonF _geoPoly;
};

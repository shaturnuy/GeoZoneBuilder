#include "MinimumAreaZoneBuilder.h"
#include <QLineF>

QPolygonF MinimumAreaZoneBuilder::buildZone(QVector<QPointF> &&points)
{
    if (points.size() < 3)
        return QPolygonF();


    QPointF start = *std::min_element(points.begin(), points.end(), [](const QPointF &a, const QPointF &b) {
        return (a.x() < b.x()) || (qFuzzyCompare(a.x(), b.x()) && a.y() < b.y());
    });

    std::sort(points.begin(), points.end(), [start](const QPointF& a, const QPointF& b) {
        QPointF vA = a - start;
        QPointF vB = b - start;

        double cross = vA.x() * vB.y() - vA.y() * vB.x();

        if (!qFuzzyIsNull(cross))
            return cross > 0;

        return QLineF(start, a).length() < QLineF(start, b).length();
    });


    return QPolygonF(points);
}

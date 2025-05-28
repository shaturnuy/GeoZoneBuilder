#include "ConvexZoneBuilder.h"
#include "qline.h"

QPolygonF ConvexZoneBuilder::buildZone(QVector<QPointF> &&points)
{
    if (points.size() < 3)
        return QPolygonF();


    QPolygonF zone;

    QPointF start = *std::min_element(points.begin(), points.end(), [](const QPointF &a, const QPointF &b) {
        return (a.x() < b.x()) || (qFuzzyCompare(a.x(), b.x()) && a.y() < b.y());
    });

    QPointF current = start;
    do
    {
        zone << current;

        QPointF best = points[0];
        for (const QPointF &candidate : std::as_const(points))
        {
            if (candidate == current)
                continue;

            const QPointF vBest = best - current;
            const QPointF vCandidate = candidate - current;
            const double cross = vBest.x() * vCandidate.y() - vBest.y() * vCandidate.x();
            const double candidateVLen = QLineF(current, candidate).length();
            const double bestVLen = QLineF(current, best).length();


            if (best == current || cross > 0 || (qFuzzyIsNull(cross) && candidateVLen > bestVLen))
                best = candidate;
        }
        current = best;

    } while (current != start);

    return zone;
}

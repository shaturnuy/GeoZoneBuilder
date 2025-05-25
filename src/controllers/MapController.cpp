#include "MapController.h"

void MapController::handleChildMousePress(QMouseEvent* event)
{
    if (event->button() == Qt::RightButton)
    {
        const QPointF geoPos = this->mapToScene(event->pos());
        emit mouseRightClicked(geoPos.x(), geoPos.y());
    }
}

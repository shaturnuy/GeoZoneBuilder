#include "MapController.h"

MapController::MapController(MapGraphicsScene* scene, QWidget* parent) :
    MapGraphicsView(scene, parent)
{
}

void MapController::handleChildMouseMove(QMouseEvent* event)
{
    QPointF geoPos = this->mapToScene(event->pos());
    emit cursorGeoPositionChanged(geoPos.x(), geoPos.y());
}

void MapController::handleChildMousePress(QMouseEvent* event)
{
    QPointF geoPos = this->mapToScene(event->pos());
    emit mouseClicked(geoPos.x(), geoPos.y());
}

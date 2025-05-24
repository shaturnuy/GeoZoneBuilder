#pragma once

#include "MapGraphicsView.h"

class MapController : public MapGraphicsView
{
    Q_OBJECT

public:
    explicit MapController(MapGraphicsScene* scene = nullptr, QWidget* parent = nullptr);

signals:
    void cursorGeoPositionChanged(double lon, double lat);
    void mouseClicked(double lon, double lat);

protected slots:
    void handleChildMouseMove(QMouseEvent* event) override;
    void handleChildMousePress(QMouseEvent* event) override;
};

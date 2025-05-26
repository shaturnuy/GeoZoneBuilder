#pragma once

#include "MapGraphicsView.h"

class MapController : public MapGraphicsView
{
    Q_OBJECT

public:
    explicit MapController(MapGraphicsScene* scene = nullptr, QWidget* parent = nullptr) : MapGraphicsView{scene, parent} {};

signals:
    void mouseRightClicked(double lat, double lon);

protected slots:
    void handleChildMousePress(QMouseEvent* event) override;
};

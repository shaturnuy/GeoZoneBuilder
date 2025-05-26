#pragma once

#include <QObject>
#include "model/PointModel.h"
#include "model/zone/AbstractZoneBuilder.hpp"
// #include "model/point/AbstractPoint.h"
#include "controllers/ZoneController.h"

class ZoneManager : public QObject
{
    Q_OBJECT

public:
    explicit ZoneManager(PointModel* model, QObject* parent = nullptr);
    ~ZoneManager();

private slots:
    void onPointModelChanged();

private:
    std::vector<AbstractPoint*> pointsByType(ZoneType type);

private:
    PointModel* m_model;
    std::vector<ZoneController*> m_zoneControllers;
};

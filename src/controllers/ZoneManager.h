#pragma once

#include <QObject>
#include "model/PointModel.h"
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
    std::map<ZoneType, ZoneController*> m_zoneControllers;
};

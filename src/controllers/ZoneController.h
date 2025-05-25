#pragma once

#include <QObject>
#include "model/PointModel.h"
#include "model/zone/IZoneBuilder.hpp"

class ZoneController : public QObject
{
    Q_OBJECT

public:
    ZoneController(PointModel *model, IZoneBuilder *builder, QObject *parent = nullptr);
    ~ZoneController();

    void setBuilder(IZoneBuilder *newBuilder);

private slots:
    void updateZone();

private:
    PointModel *m_model;
    IZoneBuilder *m_builder;
};

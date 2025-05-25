#include "ZoneController.h"

ZoneController::ZoneController(PointModel *model, IZoneBuilder *builder, QObject *parent) :
    QObject{parent},
    m_model{model},
    m_builder{builder}
{
    connect(m_model, &PointModel::dataChanged, this, &ZoneController::updateZone);
    connect(m_model, &PointModel::rowsInserted, this, &ZoneController::updateZone);
    connect(m_model, &PointModel::rowsRemoved, this, &ZoneController::updateZone);

    updateZone();
}

void ZoneController::setBuilder(IZoneBuilder *newBuilder)
{
    m_builder = newBuilder;
    updateZone();
}

void ZoneController::updateZone()
{
}

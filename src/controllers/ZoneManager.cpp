#include "ZoneManager.h"

ZoneManager::ZoneManager(PointModel *model, QObject *parent) :
    QObject{parent},
    m_model{model}
{
    connect(m_model, &PointModel::dataChanged, this, &ZoneManager::onPointModelChanged);
    connect(m_model, &PointModel::rowsInserted, this, &ZoneManager::onPointModelChanged);
    connect(m_model, &PointModel::rowsRemoved, this, &ZoneManager::onPointModelChanged);
}

ZoneManager::~ZoneManager()
{
    for (ZoneController *controller : m_zoneControllers)
        controller->deleteLater();
}

void ZoneManager::onPointModelChanged()
{
    for (ZoneController *controller : m_zoneControllers)
    {
        controller->updateZone(pointsByType(controller->type()));
    }
}

std::vector<AbstractPoint*> ZoneManager::pointsByType(ZoneType type)
{
    std::vector<AbstractPoint*> points;
    for (AbstractPoint *point : m_model->points())
    {
        if (point->type() == type)
            points.push_back(point);
    }
    return points;
}

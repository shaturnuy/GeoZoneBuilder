#include "ZoneManager.h"

#include "model/zone/ConvexZoneBuilder.h"
#include "model/zone/MinimumAreaZoneBuilder.h"

ZoneManager::ZoneManager(PointModel *model, QObject *parent) :
    QObject{parent},
    m_model{model}
{
    m_zoneControllers.insert({ZoneType::Convex, new ZoneController(ZoneType::Convex, new ConvexZoneBuilder(), this)});
    m_zoneControllers.insert({ZoneType::MinimumArea, new ZoneController(ZoneType::MinimumArea, new MinimumAreaZoneBuilder(), this)});

    connect(m_model, &PointModel::dataChanged, this, &ZoneManager::onPointModelChanged);
    connect(m_model, &PointModel::rowsInserted, this, &ZoneManager::onPointModelChanged);
    connect(m_model, &PointModel::rowsRemoved, this, &ZoneManager::onPointModelChanged);
}

ZoneManager::~ZoneManager()
{
    for (const auto& [type, controller] : m_zoneControllers)
        controller->deleteLater();
}

void ZoneManager::onPointModelChanged()
{
    for (const auto& [type, controller] : m_zoneControllers)
        controller->updateZone(pointsByType(controller->type()));
}

std::vector<AbstractPoint*> ZoneManager::pointsByType(ZoneType type)
{
    const QVector<AbstractPoint*> allPoints = m_model->points();

    std::vector<AbstractPoint*> points;
    for (AbstractPoint *point : allPoints)
    {
        if (point->type() == type)
            points.push_back(point);
    }
    return points;
}

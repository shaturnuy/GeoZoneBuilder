#include "ZoneManager.h"

ZoneManager::ZoneManager(PointModel *model, QObject *parent) :
    QObject{parent},
    m_model{model}
{
    for (int iter = 0; iter < static_cast<int>(ZoneType::COUNT); ++iter) // простите....
    {
        ZoneType type = static_cast<ZoneType>(iter);
        m_zoneControllers.insert({type, new ZoneController(type, this)});
    }

    connect(m_model, &PointModel::dataChanged, this, &ZoneManager::onPointModelChanged);
    connect(m_model, &PointModel::rowsInserted, this, &ZoneManager::onPointModelChanged);
    connect(m_model, &PointModel::rowsRemoved, this, &ZoneManager::onPointModelChanged);
}

ZoneManager::~ZoneManager()
{
    for (const auto& [type, controller] : m_zoneControllers)
        controller->deleteLater();
}

QList<AbstractZoneItem*> ZoneManager::items() const
{
    QList<AbstractZoneItem*> items;
    for (const auto& [type, controller] : m_zoneControllers)
        items.append(controller->item());
    return items;
}

void ZoneManager::onPointModelChanged()
{
    for (const auto& [type, controller] : m_zoneControllers)
        controller->updateZone(pointsByType(controller->type()));
}

QVector<QPointF> ZoneManager::pointsByType(ZoneType type)
{
    QVector<QPointF> points;
    for (const AbstractPoint *point : m_model->points())
    {
        if (point->type() == type)
            points.append(point->toPointF());
    }
    return points;
}

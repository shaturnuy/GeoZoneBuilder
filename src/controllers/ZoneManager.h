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

    QList<AbstractZoneItem*> items() const;

private slots:
    void onPointModelChanged();

private:
    QVector<QPointF> pointsByType(ZoneType type);

private:
    PointModel *m_model;
    std::map<ZoneType, ZoneController*> m_zoneControllers;
};

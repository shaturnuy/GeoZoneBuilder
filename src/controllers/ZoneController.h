#pragma once

#include <QObject>

#include "global.hpp"
#include "model/zone/AbstractZoneBuilder.hpp"
#include "view/zone/AbstractZoneItem.h"

class ZoneController : public QObject
{
    Q_OBJECT

public:
    ZoneController(ZoneType type, AbstractZoneBuilder *builder, QObject *parent = nullptr);
    ~ZoneController() {};

    inline ZoneType type() const { return m_type; }
    inline AbstractZoneItem* item() const { return m_item; }

    void updateZone(const QVector<AbstractPoint*> points);

private:
    ZoneType m_type;
    AbstractZoneBuilder *m_builder;
    AbstractZoneItem *m_item;
};

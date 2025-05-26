#pragma once

#include <QObject>

#include "global.hpp"
#include "model/zone/AbstractZoneBuilder.hpp"

class ZoneController : public QObject
{
    Q_OBJECT

public:
    ZoneController(ZoneType type, AbstractZoneBuilder *builder, QObject *parent = nullptr);
    ~ZoneController() {};

    inline ZoneType type() const { return m_type; }

    void updateZone(const std::vector<AbstractPoint*> points);

private:
    ZoneType m_type;
    AbstractZoneBuilder *m_builder;
};

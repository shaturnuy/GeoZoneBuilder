#pragma once

#include <QObject>

#include "global.hpp"

class AbstractPoint : public QObject
{
    Q_OBJECT

public:
    AbstractPoint(ZoneType type = ZoneType::Convex, double latitude = 0.0, double longitude = 0.0) :
        m_type{type}, m_latitude{latitude}, m_longitude{longitude} {}

    virtual ~AbstractPoint() = 0;


    inline double latitude() const { return m_latitude; }
    inline double longitude() const { return m_longitude; }

    inline ZoneType type() const { return m_type; }
    inline QString typeName() const { return zoneTypeString(m_type); }

    inline QPointF toPointF() const { return QPointF(m_longitude, m_latitude); }

    void setPosition(double latitude, double longitude);

signals:
    void posChanged();

protected:
    ZoneType m_type;

    double m_latitude;
    double m_longitude;
};

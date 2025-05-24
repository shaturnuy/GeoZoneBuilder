#pragma once

#include <QUuid>

class AbstractPoint
{
public:
    enum class Type
    {
        Type1
    };

public:
    AbstractPoint(double lat = 0.0, double lon = 0.0, Type type = Type::Type1) :
        m_latitude{lat}, m_longitude{lon}, m_id{QUuid::createUuid()}, m_type{type} {}

    virtual ~AbstractPoint() = default;


    inline double latitude() const { return m_latitude; }
    inline void setLatitude(double latitude) { m_latitude = latitude; }

    inline double longitude() const { return m_longitude; }
    inline void setLongitude(double longitude) { m_longitude = longitude; }

    inline QUuid id() const { return m_id; }
    inline Type type() const { return m_type; }

    virtual QString typeName() const = 0;

protected:
    double m_latitude;
    double m_longitude;

    QUuid m_id;
    Type m_type;
};

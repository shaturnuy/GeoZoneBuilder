#pragma once

#include <QObject>
#include <QUuid>

class AbstractPoint : public QObject
{
    Q_OBJECT

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
    inline double longitude() const { return m_longitude; }

    inline QUuid id() const { return m_id; }
    inline Type type() const { return m_type; }

    void setPosition(double latitude, double longitude);

    virtual QString typeName() const = 0;

signals:
    void posChanged();

protected:
    double m_latitude;
    double m_longitude;

    QUuid m_id;
    Type m_type;
};

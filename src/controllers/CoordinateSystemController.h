#pragma once

#include <QObject>

class CoordinateSystemController : public QObject
{
    Q_OBJECT

public:
    enum class CoordinateSystem
    {
        WGS84,
        SK42
    };

public:
    static CoordinateSystemController& instance();

    inline CoordinateSystem system() const { return m_system; };
    void setSystem(CoordinateSystem system);
    QString systemString() const;

    // https://gis-lab.info/qa/wgs84-sk42-wgs84-formula.html
    void wgs84ToSk42(double lat, double lon, double &rlat, double &rlon);


    CoordinateSystemController(const CoordinateSystemController&) = delete;
    CoordinateSystemController& operator=(const CoordinateSystemController&) = delete;

signals:
    void coordinateSystemChanged(CoordinateSystem system);

private:
    CoordinateSystemController() : m_system{CoordinateSystem::WGS84} {};
    ~CoordinateSystemController() {};

    CoordinateSystem m_system;
};

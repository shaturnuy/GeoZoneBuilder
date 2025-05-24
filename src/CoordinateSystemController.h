#pragma once

#include <QObject>

class CoordinateSystemController : public QObject
{
    Q_OBJECT

public:
    enum class CoordinateSystem {
        WGS84,
        SK42
    };

public:
    static CoordinateSystemController& instance();

    inline CoordinateSystem system() const { return m_system; };
    void setSystem(CoordinateSystem system);
    QString systemString() const;


    CoordinateSystemController(const CoordinateSystemController&) = delete;
    CoordinateSystemController& operator=(const CoordinateSystemController&) = delete;

signals:
    void coordinateSystemChanged(CoordinateSystem system);

private:
    CoordinateSystemController();
    ~CoordinateSystemController() {};

    CoordinateSystem m_system;
};

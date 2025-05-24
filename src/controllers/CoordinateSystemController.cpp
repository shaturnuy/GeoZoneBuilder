#include "CoordinateSystemController.h"

#include <cmath>

CoordinateSystemController& CoordinateSystemController::instance()
{
    static CoordinateSystemController instance;
    return instance;
}

void CoordinateSystemController::setSystem(CoordinateSystem system)
{
    if (m_system != system)
    {
        m_system = system;
        emit coordinateSystemChanged(system);
    }
}

QString CoordinateSystemController::systemString() const
{
    switch (m_system)
    {
    case CoordinateSystem::WGS84:   return "WGS-84";
    case CoordinateSystem::SK42:    return "СК-84";
    default:                        return QString{};
    }
}

void CoordinateSystemController::wgs84ToSk42(double lat, double lon, double &rlat, double &rlon)
{
    constexpr double Pi = 3.14159265358979; // Число Пи
    constexpr double ro = 206264.8062;      // Число угловых секунд в радиане

    // Эллипсоид Красовского
    constexpr double aP = 6378245.0;            // Большая полуось
    constexpr double alP = 1.0 / 298.3;         // Сжатие
    constexpr double e2P = 2 * alP - alP * alP; // Квадрат эксцентриситета

    // Эллипсоид WGS84 (GRS80, эти два эллипсоида сходны по большинству параметров)
    constexpr double aW = 6378137.0;            // Большая полуось
    constexpr double alW = 1.0 / 298.257223563; // Сжатие
    constexpr double e2W = 2 * alW - alW * alW; // Квадрат эксцентриситета

    // Вспомогательные значения для преобразования эллипсоидов
    constexpr double a = (aP + aW) / 2.0;
    constexpr double e2 = (e2P + e2W) / 2.0;
    constexpr double da = aW - aP;
    constexpr double de2 = e2W - e2P;

    // Линейные элементы трансформирования, в метрах
    constexpr double dx = 23.92;
    constexpr double dy = -141.27;
    constexpr double dz = -80.9;

    // Угловые элементы трансформирования, в секундах
    constexpr double wx = 0.0;
    constexpr double wy = 0.0;
    constexpr double wz = 0.0;

    // Дифференциальное различие масштабов
    constexpr double ms = 0.0;

    const auto dB = [&](double Bd, double Ld, double H) -> double
    {
        double B = Bd * Pi / 180.0;
        double L = Ld * Pi / 180.0;
        double M = a * (1 - e2) / std::pow(1 - e2 * std::sin(B) * std::sin(B), 1.5);
        double N = a / std::sqrt(1 - e2 * std::sin(B) * std::sin(B));

        return ro / (M + H) *
               (N / a * e2 * std::sin(B) * std::cos(B) * da +
               (N * N / (a * a) + 1) * N * std::sin(B) * std::cos(B) * de2 / 2.0 -
               (dx * std::cos(L) + dy * std::sin(L)) * std::sin(B) + dz * std::cos(B)) -
               wx * std::sin(L) * (1 + e2 * std::cos(2 * B)) +
               wy * std::cos(L) * (1 + e2 * std::cos(2 * B)) -
               ro * ms * e2 * std::sin(B) * std::cos(B);
    };

    const auto dL = [&](double Bd, double Ld, double H) -> double
    {
        double B = Bd * Pi / 180.0;
        double L = Ld * Pi / 180.0;
        double N = a / std::sqrt(1 - e2 * std::sin(B) * std::sin(B));

        return ro / ((N + H) * std::cos(B)) * (-dx * std::sin(L) + dy * std::cos(L)) +
               std::tan(B) * (1 - e2) * (wx * std::cos(L) + wy * std::sin(L)) - wz;
    };

    rlat = lat - dB(lat, lon, 0) / 3600.0;
    rlon = lon - dL(lat, lon, 0) / 3600.0;
}

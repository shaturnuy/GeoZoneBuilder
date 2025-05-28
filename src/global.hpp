#pragma once

#include <QString>

enum class ZoneType
{
    Convex,
    MinimumArea,
    COUNT
};

inline QString zoneTypeString(ZoneType type)
{
    switch (type)
    {
    case ZoneType::Convex:      return "Выпукл.";
    case ZoneType::MinimumArea: return "Мин. S";
    default:                    return QString();
    }
}

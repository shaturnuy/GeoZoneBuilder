#pragma once

#include <QString>

enum class ZoneType
{
    Convex,
    MinimumArea
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

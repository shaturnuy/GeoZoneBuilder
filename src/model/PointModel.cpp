#include "PointModel.h"

#include "controllers/CoordinateSystemController.h"

PointModel::PointModel(QObject *parent) :
    QAbstractListModel{parent}
{
    connect(&CoordinateSystemController::instance(), &CoordinateSystemController::coordinateSystemChanged,
            this, [this]{ emit dataChanged(index(0, 0), index(rowCount() - 1, columnCount() - 1)); });
}

int PointModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_points.size();
}

int PointModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return Columns::Count;
}

QVariant PointModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return {};


    if (orientation == Qt::Horizontal)
    {
        switch (section)
        {
        case Columns::Latitude:     return "Широта";
        case Columns::Longitude:    return "Долгота";
        case Columns::Type:         return "Тип";
        default:                    return {};
        }
    }
    else if (orientation == Qt::Vertical)
    {
        return QString::number(section + 1);
    }

    return {};
}

QVariant PointModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
        return {};

    if (index.row() < 0 || index.row() >= m_points.size())
        return {};


    const AbstractPoint* point = m_points.at(index.row());
    const double latC{point->latitude()}, lonC{point->longitude()};
    double lat{latC}, lon{lonC};

    if (CoordinateSystemController::instance().system() == CoordinateSystemController::CoordinateSystem::SK42)
        CoordinateSystemController::instance().wgs84ToSk42(latC, lonC, lat, lon);

    switch (index.column())
    {
    case Columns::Latitude:     return QString::number(lat, 'f', 6);
    case Columns::Longitude:    return QString::number(lon, 'f', 6);
    case Columns::Type:         return point->typeName();
    default:                    return {};
    }
}

void PointModel::addPoint(AbstractPoint *point)
{
    beginInsertRows(QModelIndex(), m_points.size(), m_points.size());
    m_points.append(point);
    endInsertRows();

    connect(point, &AbstractPoint::posChanged, this, &PointModel::onPosChanged);
}

bool PointModel::removePoint(AbstractPoint *point)
{
    int row = m_points.indexOf(point);
    if (row < 0 || row >= m_points.size())
        return false;

    beginRemoveRows(QModelIndex(), row, row);
    m_points.removeAt(row);
    endRemoveRows();

    return true;
}

AbstractPoint* PointModel::pointAt(int row) const
{
    if (row < 0 || row >= m_points.size())
        return nullptr;

    return m_points.at(row);
}

QModelIndex PointModel::indexOf(AbstractPoint *point, int column) const
{
    const int row = m_points.indexOf(point);
    if (row < 0 || row >= m_points.size())
        return QModelIndex();

    return index(row, column);
}

void PointModel::onPosChanged()
{
    AbstractPoint *point = dynamic_cast<AbstractPoint*>(sender());
    if (!point) return;

    const int row = m_points.indexOf(point);
    if (row < 0 || row >= m_points.size()) return;

    emit dataChanged(index(row, Columns::Latitude), index(row, Columns::Longitude));
}

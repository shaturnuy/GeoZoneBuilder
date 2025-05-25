#pragma once

#include <QAbstractListModel>
#include <QVector>
#include <QUuid>

#include "points/AbstractPoint.h"

class PointModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Columns
    {
        Latitude = 0,
        Longitude,
        Type,
        Count
    };

public:
    explicit PointModel(QObject *parent = nullptr);


    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;


    void addPoint(AbstractPoint* point);
    bool removePoint(AbstractPoint* point);

    AbstractPoint* pointAt(int row) const;
    QModelIndex indexOf(AbstractPoint* point, int column = 0) const;

private slots:
    void onPosChanged();

private:
    QVector<AbstractPoint*> m_points;
};

#pragma once

#include <QMainWindow>

#include "controllers/MapController.h"
#include "model/PointModel.h"
#include "view/PointListView.h"
#include "view/points/AbstractPointItem.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() {};

private slots:
    void addPoint(double lat, double lon);
    void deletePoint(AbstractPointItem *item);

private:
    void createCoordinateSystemMenu();

private:
    MapController *m_mapController;

    PointModel *m_pointModel;
    PointListView *m_pointListView;
};

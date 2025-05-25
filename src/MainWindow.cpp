#include "MainWindow.h"

#include <QMenuBar>
#include <QSplitter>
#include <QHeaderView>

#include "controllers/CoordinateSystemController.h"

#include "MapGraphicsScene.h"
#include "tileSources/OSMTileSource.h"
#include "tileSources/CompositeTileSource.h"

#include "model/PointModel.h"
#include "model/points/DefaultPoint.hpp"
#include "view/points/DefaultPointItem.h"
#include "view/PointListView.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_mapController{new MapController{new MapGraphicsScene{this}, this}}
{
    createCoordinateSystemMenu();

    auto pointModel = new PointModel(this);
    auto pointListView = new PointListView(this);
    pointListView->setModel(pointModel);
    for (int i = 0; i < pointModel->columnCount(); ++i)
        pointListView->setColumnWidth(i, 60);

    QSplitter *splitter = new QSplitter(this);
    splitter->addWidget(pointListView);
    splitter->addWidget(m_mapController);
    splitter->setChildrenCollapsible(false);
    splitter->setSizes({pointListView->sizeHint().width(), 800});

    setCentralWidget(splitter);


    connect(m_mapController, &MapController::mouseRightClicked, this, [=](double lon, double lat) {
        auto point = new DefaultPoint(lat, lon);

        pointModel->addPoint(point);

        DefaultPointItem *item = new DefaultPointItem(point);
        m_mapController->scene()->addObject(item);
    });


    this->resize(800, 600);

    m_mapController->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


    QSharedPointer<OSMTileSource> osmTiles(new OSMTileSource(OSMTileSource::OSMTiles), &QObject::deleteLater);
    QSharedPointer<CompositeTileSource> composite(new CompositeTileSource(), &QObject::deleteLater);

    composite->addSourceBottom(osmTiles);
    m_mapController->setTileSource(composite);

    m_mapController->setZoomLevel(12);
    m_mapController->centerOn(30.326, 59.9407);
}

void MainWindow::createCoordinateSystemMenu()
{
    QMenu* menuCoord = menuBar()->addMenu(tr("Система координат"));

    QActionGroup* groupCoord = new QActionGroup(menuCoord);
    groupCoord->setExclusive(true);

    QAction* actionWgs84 = new QAction(tr("WGS-84"), groupCoord);
    actionWgs84->setCheckable(true);
    actionWgs84->setChecked(true);

    QAction* actionSk42 = new QAction(tr("СК-42"), groupCoord);
    actionSk42->setCheckable(true);

    menuCoord->addAction(actionWgs84);
    menuCoord->addAction(actionSk42);


    connect(groupCoord, &QActionGroup::triggered, this, [=](QAction* action) {
        if (action == actionWgs84)
            CoordinateSystemController::instance().setSystem(CoordinateSystemController::CoordinateSystem::WGS84);
        else if (action == actionSk42)
            CoordinateSystemController::instance().setSystem(CoordinateSystemController::CoordinateSystem::SK42);
    });
}

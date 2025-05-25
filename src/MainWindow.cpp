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
    m_mapController{new MapController{new MapGraphicsScene{this}, this}},
    m_pointModel{new PointModel{this}},
    m_pointListView{new PointListView{this}}
{
    createCoordinateSystemMenu();


    m_pointListView->setModel(m_pointModel);
    for (int i = 0; i < m_pointModel->columnCount(); ++i)
        m_pointListView->setColumnWidth(i, 60);


    QSplitter *splitter = new QSplitter(this);
    splitter->addWidget(m_pointListView);
    splitter->addWidget(m_mapController);
    splitter->setChildrenCollapsible(false);
    splitter->setSizes({m_pointListView->sizeHint().width(), 800});
    setCentralWidget(splitter);

    m_mapController->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    resize(800, 600);


    QSharedPointer<OSMTileSource> osmTiles(new OSMTileSource(OSMTileSource::OSMTiles), &QObject::deleteLater);
    QSharedPointer<CompositeTileSource> composite(new CompositeTileSource(), &QObject::deleteLater);
    composite->addSourceBottom(osmTiles);
    m_mapController->setTileSource(composite);
    m_mapController->setZoomLevel(12);
    m_mapController->centerOn(30.326, 59.9407);


    connect(m_mapController, &MapController::mouseRightClicked, this, &MainWindow::addPoint);
}

void MainWindow::addPoint(double lat, double lon)
{
    AbstractPoint *point = new DefaultPoint(lat, lon);
    m_pointModel->addPoint(point);

    AbstractPointItem *item = new DefaultPointItem(point);
    m_mapController->scene()->addObject(item);

    connect(item, &AbstractPointItem::deleteFromMap, this, &MainWindow::deletePoint);
}

void MainWindow::deletePoint(AbstractPointItem *item)
{
    if (!item)
        return;

    AbstractPoint *point = item->point();

    m_mapController->scene()->removeObject(item);
    // item->deleteLater();

    // const int row = m_pointModel->indexOf(point).row();
    // if (row >= 0)
        m_pointModel->removePoint(point);
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

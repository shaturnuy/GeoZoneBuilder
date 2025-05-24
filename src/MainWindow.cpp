#include "MainWindow.h"

#include <QMenuBar>

#include "CoordinateSystemController.h"
#include "MapGraphicsScene.h"
#include "tileSources/OSMTileSource.h"
#include "tileSources/CompositeTileSource.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_mapController{new MapController{new MapGraphicsScene{this}, this}}
{
    createCoordinateSystemMenu();

    this->resize(800, 600);
    setCentralWidget(m_mapController);

    setAttribute(Qt::WA_TransparentForMouseEvents);
    m_mapController->setMouseTracking(true);

    QSharedPointer<OSMTileSource> osmTiles(new OSMTileSource(OSMTileSource::OSMTiles), &QObject::deleteLater);
    QSharedPointer<CompositeTileSource> composite(new CompositeTileSource(), &QObject::deleteLater);

    composite->addSourceBottom(osmTiles);
    m_mapController->setTileSource(composite);

    m_mapController->setZoomLevel(12);
    m_mapController->centerOn(-112.202442, 40.9936234);

    connect(m_mapController, &MapController::cursorGeoPositionChanged, this, [](double x, double y) { qDebug() << x << y; });
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

    // Подключаем слот к переключению системы координат
    connect(groupCoord, &QActionGroup::triggered, this, [=](QAction* action){
        if (action == actionWgs84)
            CoordinateSystemController::instance().setSystem(CoordinateSystemController::CoordinateSystem::WGS84);
        else if (action == actionSk42)
            CoordinateSystemController::instance().setSystem(CoordinateSystemController::CoordinateSystem::SK42);
    });
}

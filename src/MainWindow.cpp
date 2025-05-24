#include "MainWindow.h"

#include "MapGraphicsScene.h"
#include "MapGraphicsView.h"
#include "tileSources/GridTileSource.h"
#include "tileSources/OSMTileSource.h"
#include "tileSources/CompositeTileSource.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->resize(800, 600);

    MapGraphicsScene * scene = new MapGraphicsScene(this);
    MapGraphicsView * view = new MapGraphicsView(scene,this);
    this->setCentralWidget(view);

    QSharedPointer<OSMTileSource> osmTiles(new OSMTileSource(OSMTileSource::OSMTiles), &QObject::deleteLater);
    QSharedPointer<GridTileSource> gridTiles(new GridTileSource(), &QObject::deleteLater);
    QSharedPointer<CompositeTileSource> composite(new CompositeTileSource(), &QObject::deleteLater);

    composite->addSourceBottom(osmTiles);
    composite->addSourceTop(gridTiles);
    view->setTileSource(composite);

    view->setZoomLevel(12);
    view->centerOn(-112.202442, 40.9936234);
}

MainWindow::~MainWindow() {}

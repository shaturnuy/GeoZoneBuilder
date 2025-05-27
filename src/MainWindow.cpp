#include "MainWindow.h"

#include <QMenuBar>
#include <QSplitter>

#include "controllers/CoordinateSystemController.h"

#include "MapGraphicsScene.h"
#include "tileSources/OSMTileSource.h"
#include "tileSources/CompositeTileSource.h"

#include "view/PointItemFactory.hpp"
#include "view/PointTypePopup.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_mapController{new MapController{new MapGraphicsScene{this}, this}},
    m_pointModel{new PointModel{this}},
    m_pointListView{new PointListView{this}},
    m_zoneManager{new ZoneManager{m_pointModel, this}}
{
    createCoordinateSystemMenu();


    m_pointListView->setModel(m_pointModel);
    for (int i = 0; i < m_pointModel->columnCount(); ++i)
        m_pointListView->setColumnWidth(i, 60);


    QSplitter *splitter = new QSplitter(this);
    splitter->addWidget(m_pointListView);
    splitter->addWidget(m_mapController);
    splitter->setChildrenCollapsible(false);
    splitter->setSizes({m_pointListView->sizeHint().width() + 10, 800});
    setCentralWidget(splitter);

    m_mapController->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    resize(800, 600);


    QSharedPointer<OSMTileSource> osmTiles(new OSMTileSource(OSMTileSource::OSMTiles), &QObject::deleteLater);
    QSharedPointer<CompositeTileSource> composite(new CompositeTileSource(), &QObject::deleteLater);
    composite->addSourceBottom(osmTiles);
    m_mapController->setTileSource(composite);
    m_mapController->setZoomLevel(12);
    m_mapController->centerOn(30.326, 59.9407);

    const auto &items = m_zoneManager->items(); // c++11 range-loop might detach Qt container
    for (auto *item : items)
        m_mapController->scene()->addObject(item);

    connect(m_mapController, &MapController::mouseRightClicked, this, &MainWindow::showPointTypeMenu);
}

void MainWindow::showPointTypeMenu(double lat, double lon)
{
    PointTypePopup *popup = new PointTypePopup(this);
    popup->move(QCursor::pos());
    popup->show();

    connect(popup, &PointTypePopup::pointTypeChosen, this, [=](ZoneType type){ createPoint(type, lat, lon); });
}

void MainWindow::createPoint(ZoneType type, double lat, double lon)
{
    AbstractPoint *point = nullptr;
    if (type == ZoneType::Convex)
        point = new ConvexPoint(lat, lon);
    else if (type == ZoneType::MinimumArea)
        point = new MinimumAreaPoint(lat, lon);

    if (!point)
        return;


    m_pointModel->addPoint(point);

    AbstractPointItem *item = PointItemFactory::create(point);
    if (!item) return;

    m_mapController->scene()->addObject(item);
    connect(item, &AbstractPointItem::deleteFromMap, this, &MainWindow::deletePoint);
}

void MainWindow::deletePoint(AbstractPointItem *item)
{
    if (!item)
        return;

    AbstractPoint *point = item->point();

    m_mapController->scene()->removeObject(item);
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

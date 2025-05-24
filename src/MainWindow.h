#pragma once

#include <QMainWindow>

#include "controllers/MapController.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() {};

private:
    void createCoordinateSystemMenu();

private:
    MapController *m_mapController;
};

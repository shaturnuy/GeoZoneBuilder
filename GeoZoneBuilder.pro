TEMPLATE    = app
TARGET      = GeoZoneBuilder

CONFIG  += c++11
QT      += core gui widgets network

DEFINES += MAPGRAPHICS_LIBRARY


HEADERS +=  $$files(src/*.h, true) \
            $$files($$PWD/3rdparty/MapGraphics/MapGraphics/*.h, true)

SOURCES +=  main.cpp \
            $$files(src/*.cpp, true) \
            $$files($$PWD/3rdparty/MapGraphics/MapGraphics/*.cpp, true)

INCLUDEPATH += src \
               $$PWD/3rdparty/MapGraphics/MapGraphics

FORMS += $$PWD/3rdparty/MapGraphics/MapGraphics/guts/CompositeTileSourceConfigurationWidget.ui

RESOURCES += $$PWD/3rdparty/MapGraphics/MapGraphics/resources.qrc

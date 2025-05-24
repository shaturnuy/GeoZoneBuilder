TEMPLATE    = app
TARGET      = GeoZoneBuilder

CONFIG  += c++17
QT      += core gui widgets

HEADERS += $$files(*.h, true)
SOURCES += $$files(*.cpp, true)

INCLUDEPATH += src \
               ../3rdparty/MapGraphics

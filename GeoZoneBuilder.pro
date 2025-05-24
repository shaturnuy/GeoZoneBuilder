TEMPLATE = subdirs
CONFIG  += ordered

SUBDIRS += 3rdparty/MapGraphics/MapGraphics
SUBDIRS += GeoZoneBuilderApp

GeoZoneBuilderApp.depends = MapGraphics

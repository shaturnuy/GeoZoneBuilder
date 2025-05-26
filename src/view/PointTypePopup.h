#pragma once

#include <QWidget>

#include "global.hpp"

class PointTypePopup : public QWidget
{
    Q_OBJECT

public:
    PointTypePopup(QWidget* parent = nullptr);

signals:
    void pointTypeChosen(ZoneType type);
};

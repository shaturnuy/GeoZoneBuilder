#include "PointTypePopup.h"

#include <QVBoxLayout>
#include <QPushButton>

#include "global.hpp"

PointTypePopup::PointTypePopup(QWidget *parent) :
    QWidget{parent, Qt::Popup}
{
    setAttribute(Qt::WA_DeleteOnClose);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    QPushButton *buttonConvex = new QPushButton(zoneTypeString(ZoneType::Convex), this);
    QPushButton *buttonMinArea = new QPushButton(zoneTypeString(ZoneType::MinimumArea), this);

    layout->addWidget(buttonConvex);
    layout->addWidget(buttonMinArea);

    connect(buttonConvex, &QPushButton::clicked, this, [this] {
        emit pointTypeChosen(ZoneType::Convex);
        close();
    });

    connect(buttonMinArea, &QPushButton::clicked, this, [this] {
        emit pointTypeChosen(ZoneType::MinimumArea);
        close();
    });
}

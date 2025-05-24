#include "PointListView.h"

#include <QHeaderView>

PointListView::PointListView(QWidget *parent) :
    QTableView{parent}
{
    horizontalHeader()->setMinimumSectionSize(60);
    horizontalHeader()->setStretchLastSection(true);

    verticalHeader()->setVisible(true);

    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSelectionMode(QAbstractItemView::SingleSelection);
}

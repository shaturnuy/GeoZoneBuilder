#pragma once

#include <QTableView>

class PointListView : public QTableView
{
    Q_OBJECT

public:
    explicit PointListView(QWidget *parent = nullptr);
};

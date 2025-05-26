#pragma once

#include <QGraphicsItem>
#include "model/point/AbstractPoint.h"
#include "MapGraphicsObject.h"

class AbstractPointItem : public MapGraphicsObject
{
    Q_OBJECT

public:
    explicit AbstractPointItem(AbstractPoint *point, MapGraphicsObject *parent = nullptr);
    virtual ~AbstractPointItem() = default;

    inline AbstractPoint* point() const { return m_point; }


    virtual void keyReleaseEvent(QKeyEvent *event) override;

    virtual QRectF boundingRect() const override = 0;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override = 0;

signals:
    void deleteFromMap(AbstractPointItem *item);

protected slots:
    void onPosChanged();

protected:
    AbstractPoint* m_point;
};

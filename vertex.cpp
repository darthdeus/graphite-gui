#include <QDebug>
#include <QGraphicsRectItem>
#include <QPen>
#include <QVariant>
#include <iostream>

#include "vertex.h"

Vertex::Vertex(QGraphicsItem *parent) :
    QGraphicsRectItem(parent)
{
    setPen(QPen());
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
}

QVariant Vertex::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant& value)
{
    if (change == QGraphicsItem::ItemPositionChange) {
        qDebug() << value;
//        arrow->updatePosition();
    }
    return value;
}

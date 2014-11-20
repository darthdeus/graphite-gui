#include <QDebug>
#include <QGraphicsRectItem>
#include <QPen>
#include <QVariant>
#include <iostream>

#include "edge.h"
#include "vertex.h"

Vertex::Vertex(QGraphicsItem *parent) :
    QGraphicsRectItem(parent)
{
    setPen(QPen());
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    setRect(0, 0, 50, 50);
}

QVariant Vertex::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant& value)
{
    if (change == QGraphicsItem::ItemPositionChange) {
        qDebug() << value;
        for (Edge* edge: edges) {
            edge->updatePosition();
        }
    }
    return value;
}

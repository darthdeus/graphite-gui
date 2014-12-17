#include <QDebug>
#include <QGraphicsEllipseItem>
#include <QPen>
#include <QVariant>

#include <iostream>
#include <memory>

#include "edge.h"
#include "vertex.h"

Vertex::Vertex(QGraphicsItem *parent) :
    QGraphicsEllipseItem(parent)
{
    setPen(QPen(QColor(90, 90, 90)));
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);   
    setFlag(QGraphicsItem::ItemIsSelectable);
    setRect(0, 0, GraphicSize, GraphicSize);
}

QVariant Vertex::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant& value)
{
    if (change == QGraphicsItem::ItemPositionChange) {
//        qDebug() << value;
        repaintEdges();
    }
    return value;
}

void Vertex::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    repaintEdges();
}

void Vertex::repaintEdges()
{
    for (Edge* edge: edges) {
        edge->updatePosition();
    }
}

void Vertex::clearEdges()
{
    edges.clear();
}

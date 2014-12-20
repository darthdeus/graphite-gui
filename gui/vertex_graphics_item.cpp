#include <QDebug>
#include <QGraphicsEllipseItem>
#include <QPen>
#include <QVariant>

#include <iostream>
#include <memory>

#include "gui/edge_graphics_item.h"
#include "gui/vertex_graphics_item.h"

VertexGraphicsItem::VertexGraphicsItem(Vertex *vertex, QGraphicsItem *parent)
    : vertex(vertex), QGraphicsEllipseItem(parent)
{
    setPen(QPen(QColor(90, 90, 90)));
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setRect(0, 0, GraphicSize, GraphicSize);
}

QVariant
VertexGraphicsItem::itemChange(QGraphicsItem::GraphicsItemChange change,
                               const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange) {
        repaintEdges();
    }
    return value;
}

void VertexGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    repaintEdges();
}

void VertexGraphicsItem::repaintEdges()
{
    for (EdgeGraphicsItem *edge : edges) {
        edge->updatePosition();
    }
}

void VertexGraphicsItem::clearEdges() { edges.clear(); }

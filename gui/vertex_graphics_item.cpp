#include <QDebug>
#include <QGraphicsEllipseItem>
#include <QPen>
#include <QVariant>
#include <QGraphicsTextItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

#include <iostream>
#include <memory>

#include "gui/edge_graphics_item.h"
#include "gui/vertex_graphics_item.h"

VertexGraphicsItem::VertexGraphicsItem(Vertex *vertex, QGraphicsItem *parent)
    : QGraphicsEllipseItem(parent), vertex(vertex)
{
    setPen(QPen(QColor(90, 90, 90)));
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setRect(0, 0, GraphicSize, GraphicSize);

    setX(vertex->x);
    setY(vertex->y);
    //    childItems().append();
}

QVariant VertexGraphicsItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange) {
        repaintEdges();
    }
    return value;
}

void VertexGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    vertex->x = x();
    vertex->y = y();
    repaintEdges();
}

void VertexGraphicsItem::repaintEdges()
{
    for (EdgeGraphicsItem *edge : edges) {
        edge->updatePosition();
    }
}

void VertexGraphicsItem::clearEdges() { edges.clear(); }

void VertexGraphicsItem::setCoordinates(float x, float y)
{
    setX(x);
    setY(y);
    vertex->x = x;
    vertex->y = y;
}

void VertexGraphicsItem::setColor(QColor color)
{
    setBrush(QBrush(color));
    vertex->color = color;
}

int VertexGraphicsItem::value() const { return vertex->value; }

bool VertexGraphicsItem::hasCoordinates() const
{
    return std::abs((long)x()) > 0.001 && std::abs((long)y()) > 0.001;
}

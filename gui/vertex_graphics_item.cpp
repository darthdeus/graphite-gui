#include <QDebug>
#include <QGraphicsEllipseItem>
#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QPen>
#include <QStyleOptionGraphicsItem>
#include <QVariant>
#include <QWidget>

#include <iostream>
#include <memory>
#include <cstdlib>

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

int VertexGraphicsItem::value() const { return vertex->value; }

bool VertexGraphicsItem::hasCoordinates() const
{
    return std::abs((long)x()) > 0.001 && std::abs((long)y()) > 0.001;
}

void VertexGraphicsItem::markSearch(bool value) {
    vertex->target = value;
//    vertex->color = value ? vertex_color::gray : vertex_color::white;
    update();
}

void VertexGraphicsItem::selected(bool value) {
    setSelected(value);
    vertex->selected = value;
}

void VertexGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    int opacity = vertex->selected ? 100 : 255;
    switch (vertex->color) {
    case vertex_color::white:
        setBrush(QBrush(QColor(120, 150, 130, opacity)));
        break;
    case vertex_color::gray:
        setBrush(QBrush(QColor(90, 100, 80, opacity)));
        break;
    case vertex_color::black:
        setBrush(QBrush(QColor(20, 50, 30, opacity)));
        break;
    }

    if (vertex->target) {
        QPen pen = QPen(QColor(100, 50, 50));
        pen.setWidth(2);
        setPen(pen);
    }

    QGraphicsEllipseItem::paint(painter, option, widget);

    QGraphicsTextItem text{};
    text.setHtml(QString("<span style='font-size: 16px; font-weight: bold; color: white'>%1</span>").arg(vertex->value));
    text.setFlag(QGraphicsItem::ItemIsSelectable, false);
    text.paint(painter, option, widget);
}

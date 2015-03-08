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

#include <limits>
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
}

QVariant VertexGraphicsItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange) {
        // aktualne neni potreba nic refreshovat
    }
    return value;
}

void VertexGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem::mouseReleaseEvent(event);
    vertex->x = x();
    vertex->y = y();
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
        setBrush(QBrush(QColor(90, 200, 80, opacity)));
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


    QString text;
    if (vertex->showDistance) {
        text = QString("%1 / %2").arg(vertex->value);

        if (vertex->distance == std::numeric_limits<int>::max()) {
            text = text.arg("inf");
        } else {
            text = text.arg(vertex->distance);
        }
    } else {
        text = QString("%1").arg(vertex->value);
    }

    if (vertex->label.length() > 0) {
        painter->setPen(QColor(Qt::black));
        QString label(vertex->label.c_str());

        auto rect = this->boundingRect();
        rect.setLeft(rect.left() + 50);
        rect.setWidth(rect.width() + 50);
        painter->drawText(rect, label);
    }

    painter->setPen(QColor(Qt::white));
    painter->drawText(this->boundingRect(), text, QTextOption(Qt::AlignCenter));
}

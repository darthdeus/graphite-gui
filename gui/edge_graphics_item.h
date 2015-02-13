#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsLineItem>
#include "lib/edge.hpp"

class VertexGraphicsItem;

class EdgeGraphicsItem : public QGraphicsLineItem
{
public:
    EdgeGraphicsItem(VertexGraphicsItem* from, VertexGraphicsItem* to, Edge* edge);

    void updatePosition();
    VertexGraphicsItem* from;
    VertexGraphicsItem* to;
    Edge* edge;

    // QGraphicsItem interface
public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // EDGE_H

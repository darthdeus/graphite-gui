#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsLineItem>

class VertexGraphicsItem;

class EdgeGraphicsItem : public QGraphicsLineItem
{
public:
    EdgeGraphicsItem(VertexGraphicsItem* from, VertexGraphicsItem* to);

    void updatePosition();
    VertexGraphicsItem* from;
    VertexGraphicsItem* to;

    // QGraphicsItem interface
public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // EDGE_H

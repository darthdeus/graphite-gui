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
};

#endif // EDGE_H

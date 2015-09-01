#ifndef EDGE_GRAPHICS_ITEM_H
#define EDGE_GRAPHICS_ITEM_H

#include <QGraphicsLineItem>
#include <QGraphicsTextItem>

#include "gui/edge_weight_text.h"
#include "lib/adjacency_list.h"

class VertexGraphicsItem;

class EdgeGraphicsItem : public QGraphicsLineItem
{
public:
    EdgeGraphicsItem(VertexGraphicsItem* from, VertexGraphicsItem* to, Edge* edge);

    void updatePosition();
    VertexGraphicsItem* from;
    VertexGraphicsItem* to;
    Edge* edge;
	EdgeWeightText* weightText_;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

};

#endif // EDGE_GRAPHICS_ITEM_H

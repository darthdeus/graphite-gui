#ifndef EDGE_WEIGHT_TEXT_H
#define EDGE_WEIGHT_TEXT_H

#include <QGraphicsTextItem>
#include <QGraphicsItem>
#include "edge.h"

class EdgeWeightText : public QGraphicsTextItem
{
public:
    EdgeWeightText(QGraphicsItem* parent) : QGraphicsTextItem(parent) {}
    Edge* edge;
};

#endif // EDGE_WEIGHT_TEXT_H

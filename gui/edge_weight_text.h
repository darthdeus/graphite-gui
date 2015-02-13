#ifndef EDGE_WEIGHT_TEXT_H
#define EDGE_WEIGHT_TEXT_H

#include <QGraphicsTextItem>
#include <QGraphicsItem>
#include "lib/edge.hpp"

class EdgeWeightText : public QGraphicsTextItem
{
public:
    EdgeWeightText(QGraphicsItem* parent) : QGraphicsTextItem(parent) {}
    Edge* edge;
};

#endif // EDGE_WEIGHT_TEXT_H

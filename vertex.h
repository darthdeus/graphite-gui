#ifndef VERTEX_H
#define VERTEX_H

#include <QVariant>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <vector>
#include "edge.h"

class Vertex : public QGraphicsEllipseItem
{
public:
    explicit Vertex(QGraphicsItem *parent = 0);

    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    std::vector<Edge*> edges;
    void repaintEdges();

private:
//    Arrow* arrow;
};

#endif // VERTEX_H

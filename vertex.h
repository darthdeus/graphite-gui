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
    static const int GraphicSize = 44;
    explicit Vertex(QGraphicsItem *parent = 0);

    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * event) override;

    std::vector<Edge*> edges;
    void repaintEdges();    
    void clearEdges();

private:
//    Arrow* arrow;
};

#endif // VERTEX_H

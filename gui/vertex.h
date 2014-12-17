#ifndef VERTEX_H
#define VERTEX_H

#include <QVariant>
#include <QGraphicsItem>
#include <QGraphicsRectItem>

#include <vector>

#include "gui/edge.h"

class VertexGraphicsItem : public QGraphicsEllipseItem
{
public:
    static const int GraphicSize = 44;
    explicit VertexGraphicsItem(QGraphicsItem *parent = 0);

    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * event) override;

    std::vector<EdgeGraphicsItem*> edges;
    void repaintEdges();
    void clearEdges();



private:
//    Arrow* arrow;
};

#endif // VERTEX_H

#ifndef VERTEX_H
#define VERTEX_H

#include <QColor>
#include <QVariant>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsScene>

#include <vector>

#include "lib/vertex.hpp"
#include "gui/edge_graphics_item.h"

class VertexGraphicsItem : public QGraphicsEllipseItem
{
public:
    static const int GraphicSize = 44;
    explicit VertexGraphicsItem(Vertex* vertex, QGraphicsItem *parent = 0);

    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * event) override;

    std::vector<EdgeGraphicsItem*> edges;
    void repaintEdges();
    void clearEdges();

    void setCoordinates(float x, float y);

    Vertex* vertex;
    int value() const;
    bool hasCoordinates() const;

    void markSearch(bool);


    // QGraphicsItem interface
public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // VERTEX_H

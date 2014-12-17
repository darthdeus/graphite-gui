#include <QPen>
#include <QLineF>
#include <QGraphicsItem>

#include "edge.h"
#include "vertex.h"

Edge::Edge(Vertex* from, Vertex* to): from(from), to(to)
{
    QPen pen;
    pen.setWidth(3);
    pen.setColor(QColor(90, 90, 90));
    setPen(pen);
}

void Edge::updatePosition() {
    int center = Vertex::GraphicSize / 2;
    QLineF line(this->mapFromItem(from, center, center), this->mapFromItem(to, center, center));

    setZValue(-1);

    setLine(line);
}

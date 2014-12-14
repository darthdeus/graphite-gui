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


//    QLineF line(rf.x(), rfy(), rt.x(), rt.y());
//    QLineF line(, to->x(), to->y());
//    from->mapToItem(this);
//    QLineF line{this->mapToItem(from, 0, 0), mapToItem(to, 0, 0)};
//    QLineF line(from->mapToItem(this, 0, 0), to->mapToItem(this, 0, 0));

    setLine(line);
}

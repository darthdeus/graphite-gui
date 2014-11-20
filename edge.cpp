#include <QPen>
#include <QLineF>
#include <QGraphicsItem>

#include "edge.h"
#include "vertex.h"

Edge::Edge(Vertex* from, Vertex* to): from(from), to(to)
{
    setPen(QPen());
}

void Edge::updatePosition() {
//    auto rf = from->rect();
//    auto rt = to->rect();

    QLineF line(this->mapFromItem(from, 0, 0), this->mapFromItem(to, 0, 0));
//    QLineF line(rf.x(), rfy(), rt.x(), rt.y());
//    QLineF line(, to->x(), to->y());
//    from->mapToItem(this);
//    QLineF line{this->mapToItem(from, 0, 0), mapToItem(to, 0, 0)};
//    QLineF line(from->mapToItem(this, 0, 0), to->mapToItem(this, 0, 0));

    setLine(line);
}

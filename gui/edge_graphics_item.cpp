#include <QPen>
#include <QLineF>
#include <QGraphicsItem>

#include "gui/edge.h"
#include "gui/vertex.h"

EdgeGraphicsItem::EdgeGraphicsItem(VertexGraphicsItem* from, VertexGraphicsItem* to): from(from), to(to)
{
    QPen pen;
    pen.setWidth(3);
    pen.setColor(QColor(90, 90, 90));
    setPen(pen);
}

void EdgeGraphicsItem::updatePosition() {
    int center = VertexGraphicsItem::GraphicSize / 2;
    QLineF line(this->mapFromItem(from, center, center), this->mapFromItem(to, center, center));

    setZValue(-1);

    setLine(line);
}

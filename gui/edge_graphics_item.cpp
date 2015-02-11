#include <QPen>
#include <QLineF>
#include <QGraphicsItem>
#include <QPolygonF>
#include <QPainter>
#include <QDebug>
#include <QSize>

#include <cmath>

#include "gui/edge_graphics_item.h"
#include "gui/vertex_graphics_item.h"

static int center_ = VertexGraphicsItem::GraphicSize / 2;

EdgeGraphicsItem::EdgeGraphicsItem(VertexGraphicsItem* from, VertexGraphicsItem* to): from(from), to(to)
{
    setFlag(GraphicsItemFlag::ItemIsSelectable);
}

void EdgeGraphicsItem::updatePosition() {
    QRectF rect(line().p1(), line().p2());
    auto s = rect.size();
    s.scale(150, 150, Qt::IgnoreAspectRatio);
    rect.setSize(s);

    scene()->invalidate(rect);
}


void EdgeGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen;
    pen.setWidth(3);
    pen.setColor(QColor(90, 90, 90));
    setPen(pen);

    QLineF line(this->mapFromItem(from, center_, center_), this->mapFromItem(to, center_, center_));
    setZValue(-1);
    setLine(line);

    QPolygonF arrowHead;
    arrowHead.clear();

    float arrowSize = 40;
    double angle = std::acos(line.dx() / line.length());

    if (line.dy() >= 0) {
        angle = -angle;
    }

    QPointF arrowP1 = line.p1() + QPointF(sin(angle + M_PI / 3) * arrowSize, cos(angle + M_PI / 3) * arrowSize);
    QPointF arrowP2 = line.p1() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize, cos(angle + M_PI - M_PI / 3) * arrowSize);
    arrowHead << line.p1() << arrowP1 << arrowP2;

    pen.setWidth(1);
    painter->setPen(pen);
    painter->setBrush(QColor(90, 90, 90));
    painter->drawPolygon(arrowHead);

    QGraphicsLineItem::paint(painter, option, widget);
}

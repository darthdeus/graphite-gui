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
//    setZValue(-1);
    double angle = std::acos(line.dx() / line.length());


    double radius = VertexGraphicsItem::GraphicSize / 2;
    QPointF v1 = line.p2() - line.p1();
    double ratio1 = radius / sqrt(v1.x() * v1.x() + v1.y() * v1.y());
    line.setP2(line.p2() - v1*ratio1);

    QPointF v2 = line.p1() - line.p2();
    double ratio2 = radius / sqrt(v2.x() * v2.x() + v2.y() * v2.y());
    line.setP1(line.p1() - v2*ratio2);

    /// Protoze QT je hloupe a ma obracene osu X
    double dy = -line.dy();
    if (dy <= 0) {
        angle = -angle;
    }

    setLine(line);

    QPolygonF arrowHead;
    arrowHead.clear();


    /// Pro zjednoduseni abychom nemuseli resit otaceni uhlu
    float arrowSize = -15;

    double arrowAngle = 1 * M_PI / 3;

    QPointF arrowP1 = line.p2() + QPointF(sin(angle + arrowAngle) * arrowSize, cos(angle + arrowAngle) * arrowSize);
    QPointF arrowP2 = line.p2() + QPointF(sin(angle + M_PI - arrowAngle) * arrowSize, cos(angle + M_PI - arrowAngle) * arrowSize);
    arrowHead << line.p2() << arrowP1 << arrowP2;

    qDebug() << arrowAngle << line.p1() << line.p2() << "\t" << (360 * angle / (2*M_PI)) << "\t" << line.dx() << "\t" << dy;

    pen.setWidth(1);
    painter->setPen(pen);
    painter->setBrush(QColor(90, 90, 90));
    painter->drawPolygon(arrowHead);

    QGraphicsLineItem::paint(painter, option, widget);
}

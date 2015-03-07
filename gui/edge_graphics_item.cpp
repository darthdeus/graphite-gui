#include <QPen>
#include <QLineF>
#include <QGraphicsItem>
#include <QPolygonF>
#include <QPainter>
#include <QDebug>
#include <QSize>
#include <QGraphicsDropShadowEffect>

#include <cmath>

#include "gui/edge_graphics_item.h"
#include "gui/edge_weight_text.h"
#include "gui/vertex_graphics_item.h"

static int center_ = VertexGraphicsItem::GraphicSize / 2;

EdgeGraphicsItem::EdgeGraphicsItem(VertexGraphicsItem* from, VertexGraphicsItem* to, Edge* edge): from(from), to(to), edge(edge)
{
    setFlag(GraphicsItemFlag::ItemIsSelectable);
    weightText_ = new EdgeWeightText(this);

    // Pro zlepseni citelnosti textu
//    auto shadow = new QGraphicsDropShadowEffect();
//    shadow->setOffset(0, 0);
//    shadow->setBlurRadius(10);
//    shadow->setColor(QColor(255, 255, 255));
//    weightText_->setGraphicsEffect(shadow);
    weightText_->setFlag(QGraphicsItem::ItemIsSelectable);
    weightText_->setHtml(QString::number(edge->weight));
    weightText_->setHtml(QString("<span style='font-weight: bold;'>%1</span>").arg(edge->weight));
    weightText_->edge = edge;
}

void EdgeGraphicsItem::updatePosition() {
    QRectF rect(line().p1(), line().p2());
    auto s = rect.size();
    s.scale(150, 150, Qt::IgnoreAspectRatio);
    rect.setSize(s);

    scene()->invalidate(rect);
}

double deg(double x) {
    return 360 * x / (2 * M_PI);
}

void EdgeGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen;
    pen.setWidth(3);
    if (edge->bridge) {
        pen.setColor(QColor(230, 230, 230));
    } else {
        // TODO - handle bridges
        pen.setColor(QColor(180, 180, 180));
    }
    setPen(pen);

    QLineF line(this->mapFromItem(from, center_, center_), this->mapFromItem(to, center_, center_));
    setZValue(-1);
    double angle = std::acos(line.dx() / line.length());

    double dx = line.dx();
    /// Protoze QT je hloupe a ma obracene osu Y
    double dy = -line.dy();

    double radius = VertexGraphicsItem::GraphicSize / 2;
    QPointF v1 = line.p1() - line.p2();
    double ratio1 = radius / sqrt(v1.x() * v1.x() + v1.y() * v1.y());
    QPointF moved1 = line.p1() - v1*ratio1;
    line.setP1(moved1);

    QPointF v2 = line.p2() - line.p1();
    double ratio2 = radius / sqrt(v2.x() * v2.x() + v2.y() * v2.y());
    QPointF moved2 = line.p2() - v2*ratio2;
    line.setP2(moved2);

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

    pen.setWidth(1);
    painter->setPen(pen);
    painter->setBrush(QColor(180, 180, 180));
    painter->drawPolygon(arrowHead);

    double weightRadius = -25;
    double x_offset = std::abs(M_PI - std::abs(angle));

    QPointF offset{x_offset * 4, 10};
//    QPointF offset = QPointF(x_shift / log(x_shift), y_shift / log(y_shift));


//    qDebug() << QString("%1\t%2\t%3\t%4").arg(x_offset).arg(M_PI/2.0 - angle).arg(dx).arg(dy);

    QPointF textPoint = line.p2() + QPointF(sin(angle + arrowAngle) * weightRadius, cos(angle + arrowAngle) * weightRadius) - offset;
    weightText_->setPos(textPoint);

    QGraphicsLineItem::paint(painter, option, widget);
}

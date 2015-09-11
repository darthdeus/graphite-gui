#include <QPen>
#include <QLineF>
#include <QGraphicsItem>
#include <QPolygonF>
#include <QPainter>
#include <QDebug>
#include <QSize>
#include <QGraphicsDropShadowEffect>

#include <cmath>
#include <sstream>

#include "gui/edge_graphics_item.h"
#include "gui/edge_weight_text.h"
#include "gui/vertex_graphics_item.h"
#include "logger.h"

const double PI = atan(1) * 4;
const int center_ = VertexGraphicsItem::GraphicSize / 2;

EdgeGraphicsItem::EdgeGraphicsItem(VertexGraphicsItem* from,
                                   VertexGraphicsItem* to, Edge* edge)
    : from(from), to(to), edge(edge) {
  setFlag(GraphicsItemFlag::ItemIsSelectable);
  weightText_ = new EdgeWeightText(this);

  weightText_->setFlag(QGraphicsItem::ItemIsSelectable);
  weightText_->setHtml(QString::number(edge->weight));
  weightText_->setHtml(
      QString("<span style='font-weight: bold;'>%1</span>").arg(edge->weight));
  weightText_->edge = edge;
}

void EdgeGraphicsItem::updatePosition() {
  QRectF rect(line().p1(), line().p2());
  auto s = rect.size();
  s.scale(150, 150, Qt::IgnoreAspectRatio);
  rect.setSize(s);

  scene()->invalidate(rect);
}

double deg(double x) { return 360 * x / (2 * PI); }

std::ostream& operator<<(std::ostream& os, QPointF point) {
  return os << "(" << point.x() << "," << point.y() << ")";
}

void EdgeGraphicsItem::paint(QPainter* painter,
                             const QStyleOptionGraphicsItem* option,
                             QWidget* widget) {
  QPen pen;
  pen.setWidth(3);
  if (edge->deleted) {
    pen.setColor(QColor(230, 230, 230));
  } else if (edge->bridge) {
    pen.setColor(QColor(230, 130, 130));
  } else {
    pen.setColor(QColor(180, 180, 180));
  }
  setPen(pen);

  auto line_start = this->mapFromItem(from, center_, center_);
  auto line_end = this->mapFromItem(to, center_, center_);
  QLineF line(line_start, line_end);
  setZValue(-1);
  double angle = std::acos(line.dx() / line.length());

  // Because the Qt y-axis is reversed
  double dy = -line.dy();

  double radius = VertexGraphicsItem::GraphicSize / 2;
  QPointF v1 = line.p1() - line.p2();
  double ratio1 = radius / sqrt(v1.x() * v1.x() + v1.y() * v1.y());
  QPointF moved1 = line.p1() - v1 * ratio1;
  line.setP1(moved1);

  QPointF v2 = line.p2() - line.p1();
  double ratio2 = radius / sqrt(v2.x() * v2.x() + v2.y() * v2.y());
  QPointF moved2 = line.p2() - v2 * ratio2;
  line.setP2(moved2);

  if (dy <= 0) {
    angle = -angle;
  }

  setLine(line);

  QPolygonF arrowHead;
  arrowHead.clear();

  /// Pro zjednoduseni abychom nemuseli resit otaceni uhlu
  float arrowSize = -15;

  double arrowAngle = 1 * PI / 3;

  QPointF arrowP1 = line.p2() + QPointF(sin(angle + arrowAngle) * arrowSize,
                                        cos(angle + arrowAngle) * arrowSize);
  QPointF arrowP2 =
      line.p2() + QPointF(sin(angle + PI - arrowAngle) * arrowSize,
                          cos(angle + PI - arrowAngle) * arrowSize);
  arrowHead << line.p2() << arrowP1 << arrowP2;

  pen.setWidth(1);
  painter->setPen(pen);
  painter->setBrush(QColor(180, 180, 180));

  if (edge->oriented) {
    painter->drawPolygon(arrowHead);
  }

  if (!edge->weighted) {
    weightText_->setVisible(false);
  }

  if (edge->oriented) {
    double weightRadius = -25;
    double x_offset = std::abs(PI - std::abs(angle));

    QPointF offset{x_offset * 4, 10};

    QPointF textPoint =
        line.p2() - offset + QPointF(sin(angle + arrowAngle) * weightRadius,
                                     cos(angle + arrowAngle) * weightRadius);
    weightText_->setPos(textPoint);
  } else {
    auto x1 = line.p1().x();
    auto x2 = line.p2().x();

    auto y1 = line.p1().y();
    auto y2 = line.p2().y();

    auto max_x = std::max(x1, x2);
    auto max_y = std::max(y1, y2);

    auto min_x = std::min(x1, x2);
    auto min_y = std::min(y1, y2);

    auto dx = (max_x - min_x) / 2.0;
    auto dy = (max_y - min_y) / 2.0;

    QPointF line_center{max_x - dx, max_y - dy};

    // std::stringstream ss;
    // ss << "p1 " << line.p1() << std::endl;
    // ss << "p2 " << line.p2() << std::endl;
    // ss << "ct " << line_center << std::endl;

    // log_event(ss.str());
    // log_event("\n");

    weightText_->setPos(line_center);
  }

  QGraphicsLineItem::paint(painter, option, widget);
}

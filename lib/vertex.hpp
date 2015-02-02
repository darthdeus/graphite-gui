#ifndef GUARD_VERTEX
#define GUARD_VERTEX

#include <iostream>
#include <ostream>
#include <list>
#include <QColor>

#include "lib/edge.hpp"

enum class vertex_color { white, gray, black };

class Vertex {
 public:
  explicit Vertex(int v) : value(v), x(0), y(0), color(vertex_color::white) {}

  Vertex(const Vertex& v) = delete;
  Vertex& operator=(const Vertex& v) = delete;

  int value;

  std::list<Edge> edges;

  float x;
  float y;

  vertex_color color;
  bool selected = false;

  void* metadata;
};

std::ostream& operator<<(std::ostream& os, const Vertex& v);

#endif


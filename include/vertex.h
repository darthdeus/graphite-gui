#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <ostream>
#include <list>
#include <limits>
#include <string>

#include "edge.h"
#include "vertex_color.h"

class Vertex {
 public:
  explicit Vertex(int v) : value(v), x(0), y(0), color(vertex_color::white) {}

  Vertex(const Vertex& v) = delete;
  Vertex& operator=(const Vertex& v) = delete;

  int value;

  std::list<Edge> edges;

  float x;
  float y;

  int distance = std::numeric_limits<int>::max();

  vertex_color color;
  bool selected = false;
  bool target = false;
  bool showDistance = false;

  int low;
  int in;

  int undeletedEdgeCount();

  std::string label;
  void* metadata;
};

std::ostream& operator<<(std::ostream& os, const Vertex& v);

#endif /* VERTEX_H */


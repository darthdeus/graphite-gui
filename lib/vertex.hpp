#ifndef GUARD_VERTEX
#define GUARD_VERTEX

#include <iostream>
#include <ostream>
#include <vector>

#include "lib/edge.hpp"

class Vertex {
 public:
  explicit Vertex(int v) : value(v), x(0), y(0) {}

  Vertex(const Vertex& v) = delete;
  Vertex& operator=(const Vertex& v) = delete;

  int value;

  std::vector<Edge> edges;

  float x;
  float y;

  void* metadata;

};

std::ostream& operator<<(std::ostream& os, const Vertex& v);

#endif


#ifndef GUARD_VERTEX
#define GUARD_VERTEX

#include <iostream>
#include <ostream>
#include <vector>

#include "lib/edge.hpp"

class vertex {
 public:
  explicit vertex(int v) : value(v) {};

  vertex(const vertex& v) = delete;
  vertex& operator=(const vertex& v) = delete;

  int value;

  std::vector<edge> edges;

  void* metadata;

};

std::ostream& operator<<(std::ostream& os, const vertex& v);

#endif


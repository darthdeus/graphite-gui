#include <algorithm>
#include <ostream>

#include "vertex.h"
#include "edge.h"

std::ostream& operator<<(std::ostream& os, const Vertex& v) {
  os << v.value << "\t";

  for (auto e : v.edges) {
    os << e.to->value << " ";
  }

  return os;
}

int Vertex::undeletedEdgeCount() {
  return std::count_if(begin(edges), end(edges),
                       [](Edge& e) { return !e.deleted; });
}

#include <ostream>

#include "lib/vertex.hpp"
#include "lib/edge.hpp"

std::ostream& operator<<(std::ostream& os, const Vertex& v) {
  os << v.value << "\t";

  for (auto e : v.edges) {
    os << e.v->value << " ";
  }

  return os;
}

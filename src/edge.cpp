#include "edge.h"
#include "vertex.h"

Edge* Edge::reverseEdge() {
  for (Edge& e : to->edges) {
    if (e.to == from) {
      return &e;
    }
  }

  return nullptr;
}

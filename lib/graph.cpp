#include <algorithm>
#include <memory>
#include <iostream>

#include "lib/graph.hpp"
#include "lib/edge.hpp"

static void vertex_not_found(const char* f, int vn1, int vn2) {
  std::cout << f << ": vertex not found " << vn1 << " --> " << vn2 << std::endl;
}

vertex* graph::add_vertex(int v) {
  auto found = find(v);

  if (found) {
    return &*found;
  } else {
    list.push_back(std::make_unique<vertex>(v));
    return list.back().get();
  }
}

void graph::connect(int vn1, int vn2) {
  auto v1 = find(vn1);
  auto v2 = find(vn2);

  if (!v1 || !v2) {
    // TODO - temporary for now
    vertex_not_found("graph::connect", vn1, vn2);
    return;
  } else {
    v1->edges.emplace_back(v2);
    v2->edges.emplace_back(v1);
  }
}

bool graph::is_connected(int vn1, int vn2) const {
  auto v1 = find(vn1);
  auto v2 = find(vn2);

  if (!v1 || !v2) {
    vertex_not_found("graph::is_connected", vn1, vn2);
    return false;
  }

  auto p = [v2](edge& e) { return e.v == v2; };
  auto found = std::find_if(begin(v1->edges), end(v1->edges), p);

  return found != end(v1->edges);
}

vertex* graph::find(int v) const {
  auto p = [v](auto& vert) { return vert->value == v; };
  auto found = std::find_if(begin(list), end(list), p);

  if (found == end(list)) {
    return nullptr;
  } else {
    return (*found).get();
  }
}


void graph::clear_metadata() {
  for (auto& v : list) {
    v->metadata = nullptr;
  }
}

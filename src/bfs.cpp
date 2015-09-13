#include <queue>
#include <iostream>

#include "vertex.h"
#include "graph.h"
#include "bfs.h"

using std::cout;
using std::endl;

void BFS::start() {
  for (auto& v : g) {
    v.color = vertex_color::white;
    v.label = "";

    for (Edge& e : v.edges) {
      e.oriented = true;
      e.weighted = false;
      e.deleted = false;
      e.bridge = false;
    }
  }

  queue_.push(start_);
}

void BFS::step() {
  if (!queue_.empty()) {
    auto v = queue_.front();
    queue_.pop();

    if (v->color == vertex_color::black) return;

    if (v == end_) {
      return;
    }

    for (Edge& e : v->edges) {
      auto neighbour = e.to;
      if (neighbour->color == vertex_color::white) {
        queue_.push(neighbour);
        neighbour->color = vertex_color::gray;
      }
    }

    v->color = vertex_color::black;
  } else {
    g.clear_metadata(false);
  }
}

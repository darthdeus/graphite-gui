#include <stack>

#include "vertex.h"
#include "graph.h"
#include "dfs.h"

DFS::DFS(Graph& g, Vertex* start, Vertex* end)
    : g(g), start_(start), end_(end) {}

void DFS::start() {
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

  stack_.push(start_);
}

void DFS::step() {
  if (!stack_.empty()) {
    auto v = stack_.top();
    stack_.pop();

    if (v->color == vertex_color::black) return;

    if (v == end_) {
      return;
    }

    for (Edge& e : v->edges) {
      auto neighbour = e.to;
      if (neighbour->color == vertex_color::white) {
        stack_.push(neighbour);
        neighbour->color = vertex_color::gray;
      }
    }

    v->color = vertex_color::black;
  } else {
    g.clear_metadata(false);
  }
}

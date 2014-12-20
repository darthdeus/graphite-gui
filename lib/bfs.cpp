#include <queue>
#include <iostream>

#include "lib/graph.hpp"
#include "lib/bfs.hpp"

using std::cout;
using std::endl;

enum class vertex_color { white, gray, black };

class graph_events {
  public:
    void vertex_selected(Vertex* v);
    void vertex_colored(Vertex* v, int color);
    void edge_changed(Edge* e);
};

struct color {
  vertex_color c;
  explicit color(vertex_color c) : c(c) {}
};

static color white(vertex_color::white);
static color gray(vertex_color::gray);
static color black(vertex_color::black);

static void color_white(Vertex* v) { v->metadata = &white; }
static void color_gray(Vertex* v) { v->metadata = &gray; }
static void color_black(Vertex* v) { v->metadata = &black; }

static bool is_white(Vertex* v) { return ((color*)v->metadata) == &white; }
// static bool is_gray(vertex* v) { return ((color*)v->metadata) == &gray; }
static bool is_black(Vertex* v) { return ((color*)v->metadata) == &black; }

BFS::BFS(Graph& g, Vertex* start, Vertex* end) : g(g), start(start), end(end) {
  for (auto& v : g.list) {
    color_white(v.get());
  }

  cout << "BFS start " << start->value << endl;

  for (Edge& e : start->edges) {
    auto v = e.v;

    cout << "pushing " << v->value << endl;
    queue.push(v);
    color_gray(v);
  }

  color_black(start);
}

int BFS::step() {
  if (!queue.empty()) {
    auto v = queue.front();
    queue.pop();

    if (is_black(v)) return -1;

    cout << "processing " << v->value << endl;
    if (v == end) {
      return v->value;
    }

    for (Edge& e : v->edges) {
      auto neighbour = e.v;

      if (is_white(neighbour)) {
        cout << "    pushing neighbour " << neighbour->value << endl;
        queue.push(neighbour);
        color_gray(neighbour);
      }

      color_black(v);
    }

    color_gray(v);

    return 0;
  } else {
    g.clear_metadata();
    return -2;
  }
}

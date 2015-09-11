#include <QDebug>
#include <algorithm>
#include <cassert>
#include <memory>
#include <limits>
#include <iostream>

#include "graph.h"
#include "edge.h"
#include "utils.h"

static void vertex_not_found(const char* f, int vn1, int vn2) {
  std::cout << f << ": vertex not found " << vn1 << " --> " << vn2 << std::endl;
}

Vertex& Graph::add_vertex(int n) {
  if (n > vertex_counter_) vertex_counter_ = n;
  auto found = find(n);

  if (found) {
    qDebug() << "Tried to add existing vertex" << n;
    return *found;
  } else {
    qDebug() << "Added vertex" << n;
    list.emplace_back(n);
    return list.back();
  }
}

Vertex& Graph::add_vertex() { return add_vertex(++vertex_counter_); }

void Graph::connect(Vertex& v1, Vertex& v2) {
  connect_oriented(v1, v2);
  connect_oriented(v2, v1);
}

void Graph::connect(int vn1, int vn2) {
  connect_oriented(vn1, vn2);
  connect_oriented(vn2, vn1);
}

void Graph::connect_oriented(int vn1, int vn2, int weight) {
  auto v1 = find(vn1);
  auto v2 = find(vn2);

  if (!v1 || !v2) {
    vertex_not_found("graph::connect", vn1, vn2);
    return;
  } else {
    connect_oriented(*v1, *v2, weight);
  }
}

void Graph::connect_oriented(Vertex& v1, Vertex& v2, int weight) {
  v1.edges.emplace_back(&v2, &v1, weight);
  qDebug() << "Connected" << v1.value << v2.value;
}

void Graph::disconnect(int vn1, int vn2) {
  disconnect_oriented(vn1, vn2);
  disconnect_oriented(vn2, vn1);
}

void Graph::disconnect_oriented(int vn1, int vn2) {
  auto v1 = find(vn1);
  auto v2 = find(vn2);

  if (!v1 || !v2) {
    vertex_not_found("graph::is_connected", vn1, vn2);
  }

  if (is_connected(vn1, vn2)) {
    v1->edges.remove_if([vn2](Edge& e) { return e.to->value == vn2; });
    qDebug() << "Disconnected" << vn1 << vn2;
  } else {
    qDebug() << "Trying to disconnect vertices which aren't connected" << vn1
             << vn2;
  }
}

bool Graph::is_connected(int vn1, int vn2) {
  auto* v1 = find(vn1);
  auto* v2 = find(vn2);

  if (!v1 || !v2) {
    vertex_not_found("graph::is_connected", vn1, vn2);
    return false;
  }

  return is_connected(*v1, *v2);
}

bool Graph::is_connected(Vertex& v1, Vertex& v2) {
  auto p = [&v2](Edge& e) { return e.to->value == v2.value; };
  auto found = std::find_if(std::begin(v1.edges), std::end(v1.edges), p);

  return found != std::end(v1.edges);
}

void Graph::removeVertex(Vertex& v) {
  for (auto& vv : list) {
    vv.edges.remove_if([&v](Edge& edge) { return edge.to->value == v.value; });
  }

  qDebug() << "Removing vertex" << v.value << " ... current count is " << size();
  list.remove_if([&v](Vertex& p) { return p.value == v.value; });
}

void Graph::toggleEdge(int vn1, int vn2) {
  bool left = is_connected(vn1, vn2);
  bool right = is_connected(vn2, vn1);

  if (left && right) {
    qDebug() << "toogle(left && right)";
    disconnect_oriented(vn2, vn1);
  } else if (vn1 < vn2) {
    qDebug() << "toogle(left)" << vn1 << vn2 << (vn1 < vn2);

    connect_oriented(vn2, vn1);
    assert(is_connected(vn1, vn2));
    assert(is_connected(vn2, vn1));
  } else {
    qDebug() << "toogle(left)" << vn1 << vn2 << (vn1 < vn2);
    disconnect_oriented(vn1, vn2);
    connect_oriented(vn2, vn1);
  }
}

void Graph::set_start(Vertex* v) {
  if (start_) {
    start_->color = vertex_color::white;
    start_->target = false;
  }
  start_ = v;
  start_->color = vertex_color::gray;
  start_->target = true;
}

void Graph::set_end(Vertex* v) {
  if (end_) {
    end_->color = vertex_color::white;
    end_->target = false;
  }
  end_ = v;
  end_->color = vertex_color::gray;
  end_->target = true;
}

bool Graph::search_ready() const { return start_; }

Vertex* Graph::find(int v) {
  for (auto& vert : list) {
    if (vert.value == v) {
      return &vert;
    }
  }

  return nullptr;
}

void Graph::clear_metadata(bool showDistance) {
  for (auto& v : list) {
    v.color = vertex_color::white;
    v.distance = std::numeric_limits<int>::max();
    v.metadata = nullptr;
    v.showDistance = showDistance;
  }
}

std::unique_ptr<Graph> Graph::parse_stream(std::istream& is) {
  int size;
  is >> size;

  auto g = make_unique<Graph>();
  g->vertex_counter_ = 0;

  // First we need to create the vertices in order to connect them
  for (int i = 0; i < size; i++) {
    int n;
    is >> n;
    auto& v = g->add_vertex(n);
    is >> v.x;
    is >> v.y;
  }

  for (int i = 0; i < size; i++) {
    int vertex, edge_count;
    is >> vertex;
    is.get();
    is >> edge_count;
    is.get();

    int edge_to, weight;
    for (int j = 0; j < edge_count; j++) {
      is >> edge_to;
      is >> weight;
      qDebug() << "trying to connect" << vertex << edge_to;
      g->connect_oriented(vertex, edge_to, weight);
    }
  }

  return g;
}

std::ostream& operator<<(std::ostream& os, Graph& g) {
  std::size_t size = g.size();
  os << size << std::endl;

  for (auto& vertex : g) {
    os << vertex.value << " " << vertex.x << " " << vertex.y << std::endl;
  }
  os << std::endl;

  for (auto& vertex : g) {
    qDebug() << "saving vertex.value = " << vertex.value;
    os << vertex.value << ":";

    os << vertex.edges.size() << ":";
    for (Edge& edge : vertex.edges) {
      os << edge.to->value << " " << edge.weight << " ";
    }
    os << std::endl;
  }
  return os;
}

const int undefined_in = -1;

static void updateVertex(Vertex& v, int& counter, Edge* backEdge) {
  if (v.in != undefined_in) return;

  v.in = counter++;

  for (Edge& e : v.edges) {
    if (e.deleted) continue;
    if (&e == backEdge) continue;

    if (e.to->in == undefined_in) {
      // dopredna hrana
      updateVertex(*e.to, counter, e.reverseEdge());

      if (e.to->low >= e.to->in) {
        // nalezen most
        e.bridge = true;

        if (Edge* reverse = e.reverseEdge()) {
          reverse->bridge = true;
        }
      }

      v.low = std::min(v.low, e.to->low);
    } else if (e.to->in < v.in - 1) {
      // zpetna hrana
      v.low = std::min(v.low, e.to->in);
    }
  }
}

void Graph::update_bridges(Vertex*) {
  int counter = 1;

  for (auto& v : list) {
    v.in = undefined_in;
    v.low = std::numeric_limits<int>::max();

    for (auto& e : v.edges) {
      e.bridge = false;
    }
  }

  for (auto& v : list) {
    updateVertex(v, counter, nullptr);
  }
}

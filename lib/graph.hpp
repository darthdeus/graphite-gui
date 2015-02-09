#ifndef GUARD_GRAPH
#define GUARD_GRAPH

#include <memory>
#include <list>
#include <ostream>
#include "vertex.hpp"

class Graph {

 public:
  using adjacency_list = std::list<std::unique_ptr<Vertex>>;

  Vertex* add_vertex();
  void connect(int v1, int v2);
  void disconnect(int v1, int v2);
  bool is_connected(int v1, int v2) const;
  void removeVertex(Vertex* v);

  adjacency_list list;

  void set_start(Vertex* v);
  void set_end(Vertex* v);
  Vertex* start() const;
  Vertex* end() const;
  bool search_ready() const;

  void clear_metadata();
 private:
  // Try to find a vertex in the graph, otherwise return nullptr.
  Vertex* find(int n) const;

  Vertex* start_;
  Vertex* end_;
};

std::ostream& operator<<(std::ostream& os, Graph& g);

#endif


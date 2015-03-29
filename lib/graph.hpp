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
  void connect_oriented(int vn1, int vn2, int weight = 1);
  void disconnect(int v1, int v2);
  void disconnect_oriented(int vn1, int vn2);

  bool is_connected(int v1, int v2) const;
  void removeVertex(Vertex* v);

  /// Pro dva vrcholy prepina orientaci hrany, v nasledujicim poradi
  /// v1 <-> v2
  /// v1  -> v2
  /// v1 <-  v2
  void toggleEdge(int v1, int v2);

  adjacency_list list;

  void set_start(Vertex* v);
  void set_end(Vertex* v);
  Vertex* start() const;
  Vertex* end() const;
  bool search_ready() const;

  void clear_metadata(bool showDistance);
  void updateBridges(Vertex* start = nullptr);

  static Graph* parse_stream(std::istream& is);
private:
  // Try to find a vertex in the graph, otherwise return nullptr.
  Vertex* find(int n) const;
  Vertex *add_vertex(int n);

  Vertex* start_ = nullptr;
  Vertex* end_ = nullptr;
  int vertex_counter_ = 0;
};

std::ostream& operator<<(std::ostream& os, Graph& g);

#endif


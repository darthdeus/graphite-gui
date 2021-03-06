#ifndef GRAPH_H
#define GRAPH_H

#include <memory>
#include <list>
#include "vertex.h"

class Graph {
 public:
  using adjacency_list = std::list<Vertex>;

  // Container requirements
  using value_type      = Vertex;
  using reference       = value_type&;
  using const_reference = const value_type&;
  using pointer         = value_type*;
  using iterator        = adjacency_list::iterator;
  using const_iterator  = adjacency_list::const_iterator;
  using difference_type = adjacency_list::difference_type;
  using size_type       = adjacency_list::size_type;

  Vertex& add_vertex();

  void connect(int v1, int v2);
  Edge& connect(Vertex& v1, Vertex& v2);

  void connect_oriented(int vn1, int vn2, int weight = 1);
  Edge& connect_oriented(Vertex& v1, Vertex& v2, int weight = 1);

  void disconnect(int v1, int v2);
  void disconnect_oriented(int vn1, int vn2);

  bool is_connected(int v1, int v2);
  bool is_connected(Vertex& v1, Vertex& v2);
  void remove_vertex(Vertex& v);

  // Toggle edge orientation in the following order
  // v1 <-> v2
  // v1  -> v2
  // v1 <-  v2
  void toggle_edge(int v1, int v2);

  void set_start(Vertex* v);
  void set_end(Vertex* v);
  bool search_ready() const;

  void clear_metadata(bool showDistance);
  void update_bridges(Vertex* start = nullptr);

  iterator begin() { return list.begin(); }
  iterator end() { return list.end(); }
  const_iterator begin() const { return list.begin(); }
  const_iterator end() const { return list.end(); }
  const_iterator cbegin() const { return list.cbegin(); }
  const_iterator cend() const { return list.cend(); }

  size_type size() const { return list.size(); }
  size_type max_size() const { return list.max_size(); }
  bool empty() const { return list.empty(); }

  Vertex* start_ = nullptr;
  Vertex* end_ = nullptr;

  friend std::istream& operator>>(std::istream& is, Graph& g);
 private:
  // Try to find a vertex in the graph, otherwise return nullptr.
  Vertex* find(int n);
  Vertex& add_vertex(int n);

  adjacency_list list;

  int vertex_counter_ = 0;
};

std::ostream& operator<<(std::ostream& os, Graph& g);
std::istream& operator>>(std::istream& is, Graph& g);

#endif /* GRAPH_H */

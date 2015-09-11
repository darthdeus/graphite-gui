#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <queue>
#include "vertex.h"
#include "graph.h"
#include "search.h"

class vertex_distance {
 public:
  bool operator()(const Vertex* lhs, const Vertex* rhs) const {
    return lhs->distance > rhs->distance;
  }
};

class Dijkstra : public Search {
 public:
  Dijkstra(Graph& g, Vertex* source);

  void start() override;
  void step() override;

 private:
  std::priority_queue<Vertex*, std::vector<Vertex*>, vertex_distance> queue_;
  Graph& graph_;
  Vertex* source_ = nullptr;

  bool is_closed(Vertex* v);
};

#endif /* DIJKSTRA_H */

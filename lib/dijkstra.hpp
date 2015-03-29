#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <queue>
#include "lib/vertex.hpp"
#include "lib/graph.hpp"
#include "lib/search.hpp"

class vertex_distance {
public:
    bool operator() (const Vertex* lhs, const Vertex* rhs) const {
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

#endif // DIJKSTRA_H

#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <queue>
#include "lib/vertex.hpp"
#include "lib/graph.hpp"

class vertex_distance {
public:
    bool operator() (const Vertex* lhs, const Vertex* rhs) const {
       return lhs->distance > rhs->distance;
    }
};

class Dijkstra {
 public:
  Dijkstra(Graph& g, Vertex* source);

  void start();
  int step();

 private:
  Vertex* source_ = nullptr;
  std::priority_queue<Vertex*, std::vector<Vertex*>, vertex_distance> queue_;
  Graph& graph_;

  bool is_closed(Vertex* v);

};

#endif // DIJKSTRA_H

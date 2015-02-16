#ifndef GUARD_BFS
#define GUARD_BFS

#include "graph.hpp"
#include "vertex.hpp"
#include <queue>

class BFS {
 public:
  BFS(Graph& g, Vertex* start, Vertex* end);

  Graph& g;

  void start();
  int step();

 private:
  Vertex* start_;
  Vertex* end_;
  std::queue<Vertex*> queue_;
};

#endif

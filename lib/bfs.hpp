#ifndef GUARD_BFS
#define GUARD_BFS

#include "graph.hpp"
#include "vertex.hpp"
#include <queue>

class BFS {
 public:
  BFS(Graph& g, Vertex* start, Vertex* end);

  std::queue<Vertex*> queue;
  Graph& g;
  Vertex* start;
  Vertex* end;

  int step();

 private:
};

#endif

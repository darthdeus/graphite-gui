#ifndef GUARD_DFS
#define GUARD_DFS

#include <stack>
#include "lib/graph.hpp"
#include "lib/vertex.hpp"

class DFS {
 public:
  DFS(Graph& g, Vertex* start, Vertex* end);

  Graph& g;

  void start();
  int step();

 private:
  Vertex* start_;
  Vertex* end_;
  std::stack<Vertex*> stack_;
};

#endif

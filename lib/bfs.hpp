#ifndef GUARD_BFS
#define GUARD_BFS

#include "search.hpp"
#include "graph.hpp"
#include "vertex.hpp"
#include <queue>

class BFS : public Search {
 public:
  BFS(Graph& g, Vertex* start, Vertex* end);

  Graph& g;

  void start() override;
  int step() override;

 private:
  Vertex* start_;
  Vertex* end_;
  std::queue<Vertex*> queue_;
};

#endif

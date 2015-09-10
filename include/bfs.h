#ifndef BFS_H
#define BFS_H

#include <queue>
#include "search.h"
#include "graph.h"
#include "vertex.h"

class BFS : public Search {
 public:
  BFS(Graph& g, Vertex* start, Vertex* end);

  Graph& g;

  void start() override;
  void step() override;

 private:
  Vertex* start_;
  Vertex* end_;
  std::queue<Vertex*> queue_;
};

#endif /* BFS_H */

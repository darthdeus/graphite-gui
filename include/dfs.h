#ifndef DFS_H
#define DFS_H

#include <stack>
#include "search.h"
#include "graph.h"
#include "vertex.h"

class DFS : public Search {
 public:
  DFS(Graph& g, Vertex* start, Vertex* end);

  Graph& g;

  void start() override;
  void step() override;

 private:
  Vertex* start_;
  Vertex* end_;
  std::stack<Vertex*> stack_;
};

#endif /* DFS_H */

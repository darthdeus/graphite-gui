#pragma once

#include <stack>
#include "lib/search.hpp"
#include "lib/graph.hpp"
#include "lib/vertex.hpp"

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

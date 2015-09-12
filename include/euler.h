#ifndef EULER_H
#define EULER_H

#include <algorithm>
#include <stack>
#include <vector>

#include "vertex.h"
#include "search.h"
#include "graph.h"

// TODO - rewrite using recursive dfs loops
class Euler : public Search {
 public:
  Euler(Graph& g, Vertex* start);

  void start() override;
  void step() override;

 private:
  Graph& g_;
  Vertex* start_ = nullptr;
  Vertex* current_ = nullptr;

  std::stack<Vertex*> stack_;
  std::vector<Vertex*> circuit_;

  bool done = false;
};

#endif /* EULER_H */

#ifndef EULER_HPP
#define EULER_HPP

#include <algorithm>
#include <stack>
#include <vector>

#include "lib/vertex.hpp"
#include "lib/search.hpp"
#include "lib/graph.hpp"

class Euler : public Search
{
 public:
  Euler(Graph& g, Vertex* start);

  void start() override;
  int step() override;

 private:
  Graph& g_;
  Vertex* start_ = nullptr;
  Vertex* current_ = nullptr;

  std::stack<Vertex*> stack_;
  std::vector<Vertex*> circuit_;

  bool done = false;
};

#endif // EULER_HPP

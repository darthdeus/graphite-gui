#ifndef EULER_HPP
#define EULER_HPP

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
};

#endif // EULER_HPP

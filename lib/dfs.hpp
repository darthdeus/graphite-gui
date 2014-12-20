#ifndef GUARD_DFS
#define GUARD_DFS

#include <queue>

// TODO - can this be just a forward declaration?
class Graph;
class Vertex;

class DFS {
 public:
  DFS(Graph& g, Vertex* start, Vertex* end);

  std::queue<Vertex*> queue;
  Graph& g;
  Vertex* start;
  Vertex* end;

  int step();
};

#endif

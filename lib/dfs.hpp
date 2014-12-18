#ifndef GUARD_DFS
#define GUARD_DFS

#include <queue>

// TODO - can this be just a forward declaration?
class graph;
class vertex;

class dfs {
 public:
  dfs(graph& g, vertex* start, vertex* end);

  std::queue<vertex*> queue;
  graph& g;
  vertex* start;
  vertex* end;

  int step();
};

#endif

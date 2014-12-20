#ifndef GUARD_STORE
#define GUARD_STORE

#include <string>
class Graph;

class store {
 public:
  void save(const Graph& g, const std::string filename);
  Graph load(const std::string filename);
};

#endif

#ifndef GUARD_STORE
#define GUARD_STORE

#include <string>
class graph;

class store {
 public:
  void save(const graph& g, const std::string filename);
  graph load(const std::string filename);
};

#endif

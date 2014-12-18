#ifndef GUARD_EDGE
#define GUARD_EDGE

class vertex;

class edge {
 public:
  edge(vertex* v): v(v) {}

  int weight;
  vertex* v;
};

#endif

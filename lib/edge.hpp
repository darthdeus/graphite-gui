#ifndef GUARD_EDGE
#define GUARD_EDGE

class Vertex;

class Edge {
 public:
  Edge(Vertex* v): v(v) {}

  int weight;
  Vertex* v;
};

#endif

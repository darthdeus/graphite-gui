#ifndef GUARD_EDGE
#define GUARD_EDGE

class Vertex;

class Edge {
 public:
  Edge(Vertex* to, Vertex* from): from(from), to(to) {}

  int weight;
  Vertex* from;
  Vertex* to;
};

#endif

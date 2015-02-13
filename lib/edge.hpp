#ifndef GUARD_EDGE
#define GUARD_EDGE

class Vertex;

class Edge {
 public:
  Edge(Vertex* to, Vertex* from): from(from), to(to), weight(1) {}

  Vertex* from;
  Vertex* to;
  int weight;
};

#endif

#ifndef GUARD_EDGE
#define GUARD_EDGE

class Vertex;

class Edge {
 public:
//  Edge(Vertex* to, Vertex* from): from(from), to(to), weight(1) {}
  Edge(Vertex* to, Vertex* from, int weight): from(from), to(to), weight(weight) {}

  Vertex* from;
  Vertex* to;
  int weight;
  bool deleted = false;
  bool bridge = false;
};

#endif

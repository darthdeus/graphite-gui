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
  // TODO - show a ready status bar
  bool oriented = true;
  bool weighted = true;

  /// Returns the other side of the edge in an undirected graph,
  /// otherwise nullptr.
  Edge* reverseEdge();
};

#endif

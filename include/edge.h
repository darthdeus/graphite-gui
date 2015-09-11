#ifndef EDGE_H
#define EDGE_H

class Vertex;

class Edge {
 public:
  Edge(Vertex* to, Vertex* from, int weight)
      : from(from), to(to), weight(weight) {}

  Vertex* from;
  Vertex* to;
  int weight;
  bool deleted = false;
  bool bridge = false;

  bool oriented = true;
  bool weighted = true;

  /// Returns the other side of the edge in an undirected graph,
  /// otherwise nullptr.
  Edge* reverseEdge();
};

#endif /* EDGE_H */

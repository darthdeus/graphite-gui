#pragma once

class Vertex;

struct Edge {
	Vertex* from;
	Vertex* to;
	int weight;

	bool deleted = false;
	bool bridge = false;
	bool oriented = false;
	bool weighted = false;

	Edge(Vertex* from, Vertex* to);
	Edge(const Edge& rhs);

	Edge& operator=(const Edge& rhs);
	// Returns the other side of the edge in an undirected graph, otherwise nullptr.
	Edge* reverse_edge();
};
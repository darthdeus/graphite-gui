#ifndef JARNIK_H
#define JARNIK_H

#include <queue>

#include "search.h"
#include "edge.h"

class Graph;
class Vertex;

class EdgeWeightComparator {
public:
	bool operator()(const Edge* lhs, const Edge* rhs) const {
		// We want the lowest weight edges first (by default std::priority_queue expects a
		// < comparison, instead of >)
		return lhs->weight > rhs->weight;
	}
};

class Jarnik : public Search {
public:
	Jarnik(Graph& g, Vertex& start);
	void start() override;
	void step() override;
private:
	Graph& g_;
	Vertex* start_;
	std::priority_queue<Edge*, std::vector<Edge*>, EdgeWeightComparator> queue_;
};

#endif /* JARNIK_H */

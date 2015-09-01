#include <algorithm>
#include "lib/edge.hpp"
#include "lib/vertex.hpp"

Edge *Edge::reverse_edge()
{
    for (Edge& e: to->edges) {
        if (e.to == from) {
            return &e;
        }
    }

    return nullptr;
}

Edge::Edge(Vertex* from, Vertex* to) : from(from), to(to), weight(0), bridge(false) {
}

Edge::Edge(const Edge& rhs) : from(rhs.from), to(rhs.to), weight(rhs.weight), bridge(bridge) {
}

Edge& Edge::operator=(const Edge& rhs) {
	from = rhs.from;
	to = rhs.to;
	weight = rhs.weight;
	return *this;
}
#include "lib/edge.hpp"
#include "lib/vertex.hpp"

Edge *Edge::reverseEdge()
{
    for (Edge& e: to->edges) {
        if (e.to == from) {
            return &e;
        }
    }

    return nullptr;
}

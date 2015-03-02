#include <queue>
#include <iostream>

#include "lib/vertex.hpp"
#include "lib/graph.hpp"
#include "lib/bfs.hpp"

using std::cout;
using std::endl;

BFS::BFS(Graph &g, Vertex* s, Vertex* e) : g(g), start_(s), end_(e) {
}

void BFS::start() {
    for (auto &v : g.list) {
        v.get()->color = vertex_color::white;
    }

    queue_.push(start_);
}

int BFS::step() {
    if (!queue_.empty()) {
        auto v = queue_.front();
        queue_.pop();

        if (v->color == vertex_color::black)
            return -1;

        if (v == end_) {
            return v->value;
        }

        for (Edge &e : v->edges) {
            auto neighbour = e.to;
            if (neighbour->color == vertex_color::white) {
                queue_.push(neighbour);
                neighbour->color = vertex_color::gray;
            }
        }

        v->color = vertex_color::black;

        return 0;
    } else {
        g.clear_metadata(false);
        return -2;
    }
}

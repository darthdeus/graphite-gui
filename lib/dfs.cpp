#include <stack>

#include "lib/vertex.hpp"
#include "lib/graph.hpp"
#include "lib/dfs.hpp"

DFS::DFS(Graph& g, Vertex* start, Vertex* end) : g(g), start_(start), end_(end) {
}

void DFS::start() {
    for (auto &v : g.list) {
        v.get()->color = vertex_color::white;
    }

    stack_.push(start_);
}

int DFS::step() {
    if (!stack_.empty()) {
        auto v = stack_.top();
        stack_.pop();

        if (v->color == vertex_color::black)
            return -1;

        if (v == end_) {
            return v->value;
        }

        for (Edge &e : v->edges) {
            auto neighbour = e.to;
            if (neighbour->color == vertex_color::white) {
                stack_.push(neighbour);
                neighbour->color = vertex_color::gray;
            }
        }

        v->color = vertex_color::black;

        return 0;
    } else {
        g.clear_metadata();
        return -2;
    }
}

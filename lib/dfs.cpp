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

    stack.push(start_);
    start_->color = vertex_color::black;

    // TODO - implement this
}

int DFS::step() {
    // TODO - implement this
    return 0;
}

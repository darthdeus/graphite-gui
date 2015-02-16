#include <queue>
#include <iostream>

#include "lib/vertex.hpp"
#include "lib/graph.hpp"
#include "lib/bfs.hpp"

using std::cout;
using std::endl;

BFS::BFS(Graph &g, Vertex* s, Vertex* e) : g(g), start_(s), end_(e) {
}

void BFS::start()
{
    for (auto &v : g.list) {
        v.get()->color = vertex_color::white;
    }

    queue.push(start_);
    start_->color = vertex_color::black;

    // TODO - check if this breaks anything
//    for (Edge &e : start_->edges) {
//        auto v = e.to;

//        cout << "pushing " << v->value << endl;
//        queue.push(v);
//        v->color = vertex_color::gray;
//    }

//    start_->color = vertex_color::black;
}

int BFS::step()
{
    if (!queue.empty()) {
        auto v = queue.front();
        queue.pop();

        if (v->color == vertex_color::black)
            return -1;

        cout << "processing " << v->value << endl;
        if (v == end_) {
            return v->value;
        }

        for (Edge &e : v->edges) {
            auto neighbour = e.to;
            if (neighbour->color == vertex_color::white) {
                cout << "    pushing neighbour " << neighbour->value << endl;
                queue.push(neighbour);
                neighbour->color = vertex_color::gray;
            }

            v->color = vertex_color::black;
        }

        v->color = vertex_color::gray;

        return 0;
    } else {
        g.clear_metadata();
        return -2;
    }
}

#include <queue>
#include <iostream>

#include "lib/vertex.hpp"
#include "lib/graph.hpp"
#include "lib/bfs.hpp"

using std::cout;
using std::endl;

class graph_events
{
public:
    void vertex_selected(Vertex *v);
    void vertex_colored(Vertex *v, int color);
    void edge_changed(Edge *e);
};

struct color
{
    vertex_color c;
    explicit color(vertex_color c) : c(c) {}
};

//static color white(vertex_color::white);
//static color gray(vertex_color::gray);
//static color black(vertex_color::black);

//static void color_white(Vertex *v) { v->metadata = &white; }
//static void color_gray(Vertex *v) { v->metadata = &gray; }
//static void color_black(Vertex *v) { v->metadata = &black; }

//static bool is_white(Vertex *v) { return ((color *)v->metadata) == &white; }
//// static bool is_gray(vertex* v) { return ((color*)v->metadata) == &gray; }
//static bool is_black(Vertex *v) { return ((color *)v->metadata) == &black; }

BFS::BFS(Graph &g, Vertex* s, Vertex* e) : g(g), start_(s), end_(e) {
    start();
}

void BFS::start()
{
    for (auto &v : g.list) {
        v.get()->color = vertex_color::white;
    }

    cout << "BFS start " << start_->value << endl;

    for (Edge &e : start_->edges) {
        auto v = e.to;

        cout << "pushing " << v->value << endl;
        queue.push(v);
        v->color = vertex_color::gray;
    }

    start_->color = vertex_color::black;
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

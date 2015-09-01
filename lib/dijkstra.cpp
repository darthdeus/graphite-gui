#include <QDebug>
#include <limits>
#include "lib/dijkstra.hpp"
#include "lib/vertex.hpp"
#include "lib/graph.hpp"

Dijkstra::Dijkstra(Graph& g, Vertex* source): graph_(g), source_(source) { }

void Dijkstra::start() {
    for (auto& v : graph_) {
        v.distance = std::numeric_limits<int>::max();
        v.label = "";

        for (Edge& e: v.edges) {
            e.oriented = true;
            e.weighted = true;
            e.deleted = false;
        }
    }

    queue_.push(source_);
    source_->distance = 0;
}

void Dijkstra::step() {
    if (!queue_.empty()) {
        Vertex* v = queue_.top();
        queue_.pop();

        v->color = vertex_color::black;

        for (Edge& e : v->edges) {
            if (!is_closed(e.to)) {
                if (e.to->distance > e.weight + v->distance) {
                    e.to->distance = e.weight + v->distance;
                }

                e.to->color = vertex_color::gray;
                queue_.push(e.to);
            }
        }
    }

    return;
}

bool Dijkstra::is_closed(Vertex *v) {
    return v->color == vertex_color::black;
}


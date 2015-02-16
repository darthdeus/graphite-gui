#include <QDebug>
#include <limits>
#include "lib/dijkstra.hpp"
#include "lib/vertex.hpp"
#include "lib/graph.hpp"

Dijkstra::Dijkstra(Graph& g, Vertex* source): graph_(g), source_(source) { }

void Dijkstra::start() {
    for (auto& v : graph_.list) {
        v->distance = std::numeric_limits<int>::max();
    }

    queue_.push(source_);
    source_->distance = 0;
}

int Dijkstra::step() {
    if (!queue_.empty()) {
        Vertex* v = queue_.top();
        queue_.pop();

        qDebug() << "popped" << v->value << v->distance;

        v->color = vertex_color::gray;

        for (Edge& e : v->edges) {
            if (!is_closed(e.to)) {
                if (e.to->distance > e.weight + v->distance) {
                    e.to->distance = e.weight + v->distance;
                }

                queue_.push(e.to);
            }
        }
    }

    return 0; // TODO - handle end of input
}

bool Dijkstra::is_closed(Vertex *v) {
    return v->color == vertex_color::gray;
}


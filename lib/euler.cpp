#include <cassert>
#include <QDebug>
#include <limits>
#include <unordered_map>
#include <utility>

#include "lib/edge.hpp"
#include "lib/vertex.hpp"
#include "lib/euler.hpp"
#include "lib/graph.hpp"

Euler::Euler(Graph& g, Vertex* start): g_(g), start_(start) { }

void Euler::start() {
    done = false;
    current_ = start_;

    for (auto& v: g_) {
        v.label = "";

        for (Edge& e: v.edges) {
            e.oriented = false;
            e.weighted = false;
            e.deleted = false;
            e.bridge = false;

            if (!e.reverseEdge()) {
                g_.connect_oriented(e.to->value, e.from->value);
            }
       }
    }

    g_.updateBridges();
}

void Euler::step() {

    if (done) return;
    if (!current_) return;

    qDebug() << "current: " << current_->value;

    circuit_.push_back(current_);
    current_->color = vertex_color::white;

    auto is_bridge_or_deleted = [](Edge& e) { return e.bridge || e.deleted; };
    auto is_not_deleted = [](Edge& e) { return !e.deleted; };

    // If all edges are deleted (used) we're done	
    bool undeleted_count = std::count_if(current_->edges.begin(), current_->edges.end(), is_not_deleted);
    if (undeleted_count == 0) {
        qDebug() << "No edges left, done";
        done = true;

        g_.updateBridges();
        return;
    }

    bool all_bridges = std::all_of(current_->edges.begin(), current_->edges.end(), is_bridge_or_deleted);
    if (all_bridges) {
        // If we got this far there's at least one edge
        assert(current_->edges.size() > 0);

        Edge& edge = *std::find_if(current_->edges.begin(), current_->edges.end(), [](Edge& e) {
            return !e.deleted;
        });

        assert(edge.bridge);
        edge.deleted = true;
        edge.reverseEdge()->deleted = true;

        current_ = edge.to;
        current_->color = vertex_color::gray;

        qDebug() << "Only bridges left";

        g_.updateBridges();
        return;
    }

    auto res = std::find_if_not(current_->edges.begin(), current_->edges.end(), is_bridge_or_deleted);
    // There must be at least one non-bridge edge at this point
    assert(res != current_->edges.end());

    Edge& e = *res;
    e.deleted = true;
    e.reverseEdge()->deleted = true;

    current_ = e.to;
    current_->color = vertex_color::gray;

    qDebug() << "Non-bridge";
    g_.updateBridges(current_);
    return;
}

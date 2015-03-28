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

    for (auto& v: g_.list) {
        v->label = "";

        for (Edge& e: v->edges) {
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

int Euler::step() {
    g_.updateBridges();

    if (done) return 0;
    if (!current_) return 0;

    qDebug() << "current: " << current_->value;

    circuit_.push_back(current_);
    current_->color = vertex_color::white;

    auto is_bridge_or_deleted = [](Edge& e) { return e.bridge || e.deleted; };
    auto is_not_deleted = [](Edge& e) { return !e.deleted; };

    // If all edges are deleted (used) we're done
    bool undeleted_edge_count = std::count_if(current_->edges.begin(), current_->edges.end(), is_not_deleted);
    if (undeleted_edge_count == 0) {
        qDebug() << "No edges left, done";
        done = true;
        return 0;
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
        return 0;
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

    return 0;
}

//int Euler::step() {
//    if (done) return 0;
//    if (!current_) return 0;

//    bool found = false;
//    for (Edge& e: current_->edges) {
//        if (e.deleted) continue;

//        found = true;
//        e.deleted = true;
//        if (e.reverseEdge()) {
//            e.reverseEdge()->deleted = true;
//        }
//        stack_.push(current_);
//        current_ = e.to;

//        break;
//    }

//    if (!found) {
//        circuit_.push_back(current_);
//        qDebug() << "pushed" << current_->value;

//        if (!stack_.empty()) {
//            current_ = stack_.top();
//            stack_.pop();

//            if (!current_->undeletedEdgeCount()) step();
//            qDebug() << "popped from the stack" << current_->value;

//        } else {
//            done = true;
//            qDebug() << "Done, the circuit is:";

//            std::reverse(begin(circuit_), end(circuit_));

//            int i = 1;
//            for (Vertex* v: circuit_) {
//                if (v->label.length() > 0) {
//                    v->label += ", ";
//                }

//                v->label += QString("%1").arg(i++).toStdString();
//                qDebug() << v->value;
//            }
//        }
//    }

//    return 0;
//}

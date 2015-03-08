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
    current_ = start_;

    for (auto& v: g_.list) {
        for (Edge& e: v->edges) {
            e.oriented = false;
            e.weighted = false;
            e.deleted = false;

            if (!e.reverseEdge()) {
                g_.connect_oriented(e.to->value, e.from->value);
            }
       }
    }
}

int Euler::step() {
    if (!current_) return 0;

    bool found = false;
    for (Edge& e: current_->edges) {
        if (e.deleted) continue;

        found = true;
        e.deleted = true;
        if (e.reverseEdge()) {
            e.reverseEdge()->deleted = true;
        }
        stack_.push(current_);
        current_ = e.to;

        break;
    }

    if (!found) {
        circuit_.push_back(current_);
        qDebug() << "pushed" << current_->value;

        if (!stack_.empty()) {
            current_ = stack_.top();
            stack_.pop();
            qDebug() << "popped from the stack" << current_->value;

        } else {
            qDebug() << "Done, the circuit is:";

            for (Vertex* v: circuit_) {
                qDebug() << v->value;
            }
        }
    }
}

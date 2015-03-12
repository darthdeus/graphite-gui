#include <QDebug>
#include <algorithm>
#include <cassert>
#include <memory>
#include <limits>
#include <iostream>

#include "lib/graph.hpp"
#include "lib/edge.hpp"

static void vertex_not_found(const char *f, int vn1, int vn2) {
    // TODO - better logging
    std::cout << f << ": vertex not found " << vn1 << " --> " << vn2
              << std::endl;
}

Vertex* Graph::add_vertex(int n) {
    if (n > vertex_counter_) vertex_counter_ = n;
    auto found = find(n);

    if (found) {
        qDebug() << "Tried to add existing vertex" << n;
        return &*found;
    } else {
        qDebug() << "Added vertex" << n;
        list.push_back(std::unique_ptr<Vertex>(new Vertex(n)));
        return list.back().get();
    }
}

Vertex* Graph::add_vertex() {
    return add_vertex(++vertex_counter_);
}

void Graph::connect(int vn1, int vn2) {
    connect_oriented(vn1, vn2);
    connect_oriented(vn2, vn1);
}

void Graph::connect_oriented(int vn1, int vn2, int weight) {
    auto v1 = find(vn1);
    auto v2 = find(vn2);

    if (!v1 || !v2) {
        // TODO - temporary for now
        vertex_not_found("graph::connect", vn1, vn2);
        return;
    } else {
        v1->edges.emplace_back(v2, v1, weight);
        qDebug() << "Connected" << vn1 << vn2;
    }
}

void Graph::disconnect(int vn1, int vn2) {
    disconnect_oriented(vn1, vn2);
    disconnect_oriented(vn2, vn1);
}

void Graph::disconnect_oriented(int vn1, int vn2) {
    auto v1 = find(vn1);
    auto v2 = find(vn2);

    if (!v1 || !v2) {
        vertex_not_found("graph::is_connected", vn1, vn2);
    }

    if (is_connected(vn1, vn2)) {
        v1->edges.remove_if([vn2](Edge &e) { return e.to->value == vn2; });
        qDebug() << "Disconnected" << vn1 << vn2;
    } else {
        qDebug() << "Trying to disconnect vertices which aren't connected" << vn1 << vn2;
    }
}

bool Graph::is_connected(int vn1, int vn2) const
{
    auto v1 = find(vn1);
    auto v2 = find(vn2);

    if (!v1 || !v2) {
        vertex_not_found("graph::is_connected", vn1, vn2);
        return false;
    }

    auto p = [v2](Edge &e) { return e.to == v2; };
    auto found = std::find_if(begin(v1->edges), std::end(v1->edges), p);

    return found != std::end(v1->edges);
}

void Graph::removeVertex(Vertex *v)
{
    for (auto& vv : list) {
        vv->edges.remove_if([v](Edge& edge) {
            return edge.to->value == v->value;
        });
    }

    qDebug() << "Removing vertex" << v->value << " ... current count is " << list.size();
    list.remove_if([v](std::unique_ptr<Vertex>& p) {
        return p->value == v->value;
    });
}

void Graph::toggleEdge(int vn1, int vn2)
{
    bool left = is_connected(vn1, vn2);
    bool right = is_connected(vn2, vn1);

    if (left && right) {
        qDebug() << "toogle(left && right)";
        disconnect_oriented(vn2, vn1);
    } else if (vn1 < vn2) {
        qDebug() << "toogle(left)" << vn1 << vn2 << (vn1 < vn2);

        connect_oriented(vn2, vn1);
        assert(is_connected(vn1, vn2));
        assert(is_connected(vn2, vn1));
    } else {
        qDebug() << "toogle(left)" << vn1 << vn2 << (vn1 < vn2);
        disconnect_oriented(vn1, vn2);
        connect_oriented(vn2, vn1);
    }
}

void Graph::set_start(Vertex *v) {
    // TODO - also check if the vertex still exists
    if (start_) {
        start_->color = vertex_color::white;
        start_->target = false;
    }
    start_ = v;
    start_->color = vertex_color::gray;
    start_->target = true;
}

void Graph::set_end(Vertex *v) {
    if (end_) {
        end_->color = vertex_color::white;
        end_->target = false;
    }
    end_ = v;
    end_->color = vertex_color::gray;
    end_->target = true;
}

Vertex *Graph::start() const {
    return start_;
}

Vertex *Graph::end() const {
    return end_;
}

bool Graph::search_ready() const {
    // TODO - check if this is good enough
//    return start_ && end_;
    return start_;
}

Vertex *Graph::find(int v) const
{
    for (auto &vert : list) {
        if (vert->value == v) {
            return vert.get();
        }
    }

    return nullptr;
}

void Graph::clear_metadata(bool showDistance)
{
    for (auto &v : list) {
        v->color = vertex_color::white;
        v->distance = std::numeric_limits<int>::max();
        v->metadata = nullptr;
        v->showDistance = showDistance;
    }
}

Graph* Graph::parse_stream(std::istream& is)
{
    int size;
    is >> size;

    Graph* g = new Graph;
    g->vertex_counter_ = 0;

    // Napred musime vytvorit vrcholy, aby je bylo mozne pospojovat
    for	(int i = 0; i < size; i++) {
        int n;
        is >> n;
        auto v = g->add_vertex(n);
        is >> v->x;
        is >> v->y;
    }

    for	(int i = 0; i < size; i++) {
        int vertex, edge_count;
        is >> vertex;
        is.get();
        is >> edge_count;
        is.get();

        int edge_to, weight;
        for (int j = 0; j < edge_count; j++) {
            is >> edge_to;
            is >> weight;
            qDebug() << "trying to connect" << vertex << edge_to;
            g->connect_oriented(vertex, edge_to, weight);
        }
    }

    return g;
}

std::ostream& operator<<(std::ostream& os, Graph& g) {
    std::size_t size = g.list.size();
    os << size << std::endl;

    for (auto& vertex: g.list) {
       os << vertex->value << " " << vertex->x << " " << vertex->y << std::endl;
    }
    os << std::endl;

    for (auto& vertex: g.list) {
        qDebug() << "saving" << vertex->value << " = " << vertex.get()->value;
        os << vertex->value << ":";

        os << vertex->edges.size() << ":";
        for (Edge& edge: vertex->edges) {
            os << edge.to->value << " " << edge.weight << " "; // << edge.bridge << "| ";
        }
        os << std::endl;
    }
    return os;
}

const int undefined_in = -1;

void updateVertex(Vertex* v, int& counter) {
    v->in = counter++;
    for (Edge& e : v->edges) {
        if (e.to->in == undefined_in) {
            updateVertex(e.to, counter);

            if (e.to->low >= e.to->in) {
                e.bridge = true;

                if (Edge* reverse = e.reverseEdge()) {
                    reverse->bridge = true;
                }
            }

            v->low = std::min(v->low, e.to->low);
        } else if (e.to->in < v->in - 1) {
            // zpetna hrana
            v->low = std::min(v->low, e.to->in);
        }
    }
}


void Graph::updateBridges() {
    int counter = 0;

    for (auto& v : list) {
        v->in = undefined_in;
    }

    updateVertex((*list.begin()).get(),  counter);
}

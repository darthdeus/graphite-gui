#include <QDebug>
#include <algorithm>
#include <memory>
#include <iostream>

#include "lib/graph.hpp"
#include "lib/edge.hpp"

static void vertex_not_found(const char *f, int vn1, int vn2)
{
    std::cout << f << ": vertex not found " << vn1 << " --> " << vn2
              << std::endl;
}

Vertex *Graph::add_vertex()
{
    static int counter = 0;

    counter++;

    auto found = find(counter);

    if (found) {
        qDebug() << "Tried to add existing vertex" << counter;
        return &*found;
    } else {
        list.push_back(std::unique_ptr<Vertex>(new Vertex(counter)));
        qDebug() << "Added vertex" << counter;
        return list.back().get();
    }
}

void Graph::connect(int vn1, int vn2)
{
    auto v1 = find(vn1);
    auto v2 = find(vn2);

    if (!v1 || !v2) {
        // TODO - temporary for now
        vertex_not_found("graph::connect", vn1, vn2);
        return;
    } else {
        v1->edges.emplace_back(v2, v1);
        v2->edges.emplace_back(v1, v2);
    }
}

void Graph::disconnect(int vn1, int vn2)
{
    auto v1 = find(vn1);
    auto v2 = find(vn2);

    if (!v1 || !v2) {
        vertex_not_found("graph::is_connected", vn1, vn2);
    }

    if (is_connected(vn1, vn2)) {
        v1->edges.remove_if([vn2](Edge &e) { return e.to->value == vn2; });
        v2->edges.remove_if([vn1](Edge &e) { return e.to->value == vn1; });

        qDebug() << is_connected(vn1, vn2);
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
    for (Edge& e : v->edges) {
        e.to->edges.remove_if([v](Edge& edge) { return edge.to == v; });
    }

    qDebug() << "Removing vertex" << v->value << " ... current count is " << list.size();
    list.remove_if([v](std::unique_ptr<Vertex>& p) {
        return p->value == v->value;
    });

    qDebug() << "Size after removal:" << list.size();
}

void Graph::set_start(Vertex *v) {
    if (start_) start_->color = vertex_color::white;
    start_ = v;
    v->color = vertex_color::gray;
}

void Graph::set_end(Vertex *v) {
    if (end_) end_->color = vertex_color::white;
    end_ = v;
    v->color = vertex_color::gray;
}

Vertex *Graph::start() const {
    return end_;
}

Vertex *Graph::end() const {
    return start_;
}

bool Graph::search_ready() const
{
    return start_ && end_;
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

void Graph::clear_metadata()
{
    for (auto &v : list) {
        v->metadata = nullptr;
    }
}

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

Vertex *Graph::add_vertex(int v)
{
    auto found = find(v);

    if (found) {
        return &*found;
    } else {
        list.push_back(std::unique_ptr<Vertex>(new Vertex(v)));
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
    auto found = std::find_if(begin(v1->edges), end(v1->edges), p);

    return found != end(v1->edges);
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

#include <algorithm>
#include <ostream>

#include "lib/vertex.hpp"
#include "lib/edge.hpp"

//std::ostream& operator<<(std::ostream& os, const Vertex& v) {
//  os << v.value << "\t";
//
//  for (auto e : v.edges) {
//    os << e.to->value << " ";
//  }
//
//  return os;
//}
//
//int Vertex::undeletedEdgeCount() {
//    return std::count_if(begin(edges), end(edges), [](Edge& e) {
//        return !e.deleted;
//    });
//}

Vertex::Vertex(int id, const adjacency_list& list) : id_(id), list_(&list) {
}

bool Vertex::operator==(const Vertex& rhs) const {
	return id() == rhs.id() && list_ == rhs.list_;
}

bool Vertex::operator!=(const Vertex& rhs) const {
	return !(*this == rhs);
}
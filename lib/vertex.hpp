#pragma once

#include <ostream>
#include <list>
#include <limits>

#include "lib/edge.hpp"
#include "vertex_color.hpp"

//class Vertex {
// public:
//  explicit Vertex(int v) : value(v), x(0), y(0), color(vertex_color::white) {}
//
//  Vertex(const Vertex& v) = delete;
//  Vertex& operator=(const Vertex& v) = delete;
//
//  int value;
//
//  std::list<Edge> edges;
//
//  float x;
//  float y;
//
//  int distance = std::numeric_limits<int>::max();
//
//  vertex_color color;
//  bool selected = false;
//  bool target = false;
//  bool showDistance = false;
//
//  int low;
//  int in;
//
//  int undeletedEdgeCount();
//
//  std::string label;
//  void* metadata;
//};
//
//std::ostream& operator<<(std::ostream& os, const Vertex& v);

class adjacency_list;

class Vertex {
	int id_;
	const adjacency_list* list_;

public:
	// TODO - remove these later
	float x;
	float y;
	int distance = std::numeric_limits<int>::max();
	std::string label;
	vertex_color color;

	bool selected = false;
	bool target = false;
	bool showDistance = false;
	int low;
	int in;
	int out;

	// TODO - remove list here
	std::list<Edge> edges;

	Vertex(int id, const adjacency_list& list);

	int id() const { return id_; }

	bool operator==(const Vertex& rhs) const;
	bool operator!=(const Vertex& rhs) const;
};

namespace std {
	template <>
	class hash<Vertex> {
	public:
		std::size_t operator()(const Vertex& v) {
			return v.id();
		}
	};
}

#pragma once

#include <cstddef>
#include <vector>
#include <stack>
#include <string>
#include <unordered_map>
#include "vertex_color.hpp"

class vertex;
struct edge;
class adjacency_list;
struct vertex_metadata;

struct vertex_metadata {
	vertex_color color;
	std::string label;
};

struct edge {
	vertex* from;
	vertex* to;
	int weight;

    edge(vertex* from, vertex* to): from(from), to(to), weight(0) {}

    edge(const edge& rhs) : from(rhs.from), to(rhs.to), weight(rhs.weight) {}

	edge& operator=(const edge& rhs) {
		from = rhs.from;
		to = rhs.to;
		weight = rhs.weight;
		return *this;
	}
};

class vertex {
	int id_;
	const adjacency_list* list_;

public:
	std::vector<edge> edges;

	vertex(int id, const adjacency_list& list): id_(id), list_(&list) {
	}

	int id() const {
		return id_;
	}

	bool operator==(const vertex& rhs) const;

	bool operator!=(const vertex& rhs) const {
		return !(*this == rhs);
	}
};

struct vertex_hash {
	std::size_t operator()(const vertex& v) {
		return v.id();
	}
};

class dfs_iterator {
	// TODO - store this as a pointer
	adjacency_list& list_;
	std::vector<vertex*> stack_;
	std::unordered_map<vertex, vertex_metadata, vertex_hash> metadata_map_;

	// This way the only one who can create the iterator is the container itself.
	friend class adjacency_list;
	dfs_iterator(adjacency_list& list);

	static dfs_iterator create_begin(adjacency_list& list);
	static dfs_iterator create_end(adjacency_list& list);
public:

	using reference = vertex&;

	reference operator*();
	dfs_iterator& operator++();

	bool operator==(const dfs_iterator& rhs) const;

	bool operator!=(const dfs_iterator& rhs) const {
		return !(*this == rhs);
	}

};

class adjacency_list {
	int counter_;
	std::vector<vertex> list_;

public:
	friend class dfs_iterator;

	using value_type = vertex;
	using reference = value_type&;
    using const_reference = const value_type&;
	using iterator = std::vector<vertex>::iterator;
	using const_iterator = std::vector<vertex>::const_iterator;
	using difference_type = std::ptrdiff_t;
	using size_type = std::size_t;

    adjacency_list(): counter_(0) {}

	adjacency_list(const adjacency_list& rhs);
	adjacency_list(adjacency_list&& rhs);
	~adjacency_list();

	adjacency_list& operator=(const adjacency_list& rhs);
	adjacency_list& operator=(adjacency_list&& rhs);

    iterator begin() { return list_.begin(); }
    iterator end() { return list_.end(); }
    const_iterator begin() const { return list_.begin(); }
    const_iterator end() const { return list_.end(); }
    const_iterator cbegin() const { return list_.cbegin(); }
    const_iterator cend() const { return list_.cend(); }

	dfs_iterator dfs_begin();
	dfs_iterator dfs_end();

    bool operator==(const adjacency_list& rhs) const { return list_ == rhs.list_; }
    bool operator!=(const adjacency_list& rhs) const { return !(*this == rhs); }

	void swap(adjacency_list& rhs);

    size_type size() const { return list_.size(); }
    size_type max_size() const { return list_.max_size(); }
    bool empty() const { return list_.empty(); }

	vertex& add();
	vertex* find_by_id(int id);
};

inline void swap(adjacency_list& lhs, adjacency_list& rhs) {
	lhs.swap(rhs);
}

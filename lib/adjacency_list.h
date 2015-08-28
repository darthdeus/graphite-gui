#pragma once

#include <cstddef>
#include <vector>
#include <list>
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

	edge(vertex* from, vertex* to);
	edge(const edge& rhs);

	edge& operator=(const edge& rhs);
};

class vertex {
	int id_;
	const adjacency_list* list_;

public:
	std::vector<edge> edges;

	vertex(int id, const adjacency_list& list);

	int id() const { return id_; }

	bool operator==(const vertex& rhs) const;
	bool operator!=(const vertex& rhs) const;
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
	bool operator!=(const dfs_iterator& rhs) const;
};

class adjacency_list {
	int counter_;
	std::list<vertex> list_;

public:
	friend class dfs_iterator;

	using value_type = vertex;
	using reference = value_type&;
	using const_reference = const reference;
	using iterator = std::list<vertex>::iterator;
	using const_iterator = std::list<vertex>::const_iterator;
	using difference_type = std::ptrdiff_t;
	using size_type = std::size_t;

	adjacency_list();
	adjacency_list(const adjacency_list& rhs);
	adjacency_list(adjacency_list&& rhs);
	~adjacency_list();

	adjacency_list& operator=(const adjacency_list& rhs);
	adjacency_list& operator=(adjacency_list&& rhs);

	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;
	const_iterator cbegin() const;
	const_iterator cend() const;

	dfs_iterator dfs_begin();
	dfs_iterator dfs_end();

	bool operator==(const adjacency_list& rhs) const;
	bool operator!=(const adjacency_list& rhs) const;

	void swap(adjacency_list& rhs);
	size_type size() const;
	size_type max_size() const;
	bool empty() const;

	vertex& add();
	vertex* find_by_id(int id);

	void connect(vertex& a, vertex& b, bool oriented = false);
	// Returns true only if both vertices exist.
	bool connect(int a, int b, bool oriented = false);

	void disconnect(vertex& a, vertex& b, bool oriented = false);
	bool disconnect(int a, int b, bool oriented = false);
	
};

inline void swap(adjacency_list& lhs, adjacency_list& rhs) {
	lhs.swap(rhs);
}

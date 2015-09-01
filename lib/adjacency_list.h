#pragma once

#include <vector>
#include <list>

#include "lib/vertex.hpp"

class adjacency_list;

class dfs_iterator {
public:
	using pointer = Vertex*;
	using reference = Vertex&;

	reference operator*();
	dfs_iterator& operator++();

	bool operator==(const dfs_iterator& rhs) const;
	bool operator!=(const dfs_iterator& rhs) const;

	pointer operator->() const;

private:
	// TODO - store this as a pointer
	adjacency_list& list_;
	std::vector<Vertex*> stack_;

	// This way the only one who can create the iterator is the container itself.
	friend class adjacency_list;
	dfs_iterator(adjacency_list& list);

	static dfs_iterator create_begin(adjacency_list& list);
	static dfs_iterator create_end(adjacency_list& list);
};

class adjacency_list {
	int counter_;
	std::list<Vertex> list_;

public:
	friend class dfs_iterator;

	using value_type = Vertex;
	using reference = value_type&;
	using pointer = value_type*;
	using const_reference = const reference;
	using iterator = std::list<Vertex>::iterator;
	using const_iterator = std::list<Vertex>::const_iterator;
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

	reference add();
	pointer find_by_id(int id);

	void remove(reference v);
	bool remove(int id);

	void connect(reference a, reference b, bool oriented = false);
	// Returns true only if both vertices exist.
	bool connect(int a, int b, bool oriented = false);

	void disconnect(reference a, reference b, bool oriented = false);
	bool disconnect(int a, int b, bool oriented = false);

	void toggle_edge(reference a, reference b);
	bool toggle_edge(int a, int b);

	// TODO
	void update_bridges(Vertex* start = nullptr);
	void clear_metadata(bool showDistance);
};

inline void swap(adjacency_list& lhs, adjacency_list& rhs) {
	lhs.swap(rhs);
}



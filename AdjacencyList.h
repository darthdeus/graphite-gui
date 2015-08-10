#pragma once
#include "lib/vertex.hpp"

class AdjacencyListIterator {

};

class AdjacencyList {
public:
	using value_type = Vertex;
	using reference = value_type&;
	using const_reference = const reference;
	using iterator = AdjacencyListIterator;
	using const_iterator = const AdjacencyListIterator;
	using difference_type = std::ptrdiff_t;
	using size_type = std::size_t;

	AdjacencyList();
	AdjacencyList(const AdjacencyList& rhs);
	AdjacencyList(AdjacencyList&& rhs);
	~AdjacencyList();

	AdjacencyList& operator=(const AdjacencyList& rhs);
	AdjacencyList& operator=(AdjacencyList&& rhs);

	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;
	const_iterator cbegin() const;
	const_iterator cend() const;

	bool operator==(const AdjacencyList& rhs) const;

	bool operator!=(const AdjacencyList& rhs) const {
		return !(*this == rhs);
	}

	void swap(AdjacencyList& rhs);
	size_type size() const;
	size_type max_size() const;
	bool empty() const;
};

void swap(AdjacencyList& lhs, AdjacencyList& rhs) {
	lhs.swap(rhs);
}

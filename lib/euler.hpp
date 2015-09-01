#pragma once

#include <algorithm>
#include <stack>
#include <vector>

#include "lib/vertex.hpp"
#include "lib/search.hpp"
#include "lib/adjacency_list.h"

class Euler : public Search {
public:
	Euler(adjacency_list& g, Vertex* start);

	void start() override;
	void step() override;

private:
	adjacency_list& g_;
	Vertex* start_ = nullptr;
	Vertex* current_ = nullptr;

	std::stack<Vertex*> stack_;
	std::vector<Vertex*> circuit_;

	bool done = false;
};

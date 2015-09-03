#include <algorithm>
#include <assert.h>
#include "adjacency_list.hpp"

bool vertex::operator==(const vertex& rhs) const {
	return id() == rhs.id() && list_ == rhs.list_;
}

dfs_iterator::dfs_iterator(adjacency_list& list) : list_(list) {}

dfs_iterator dfs_iterator::create_begin(adjacency_list& list) {
	if (list.empty()) return create_end(list);

	dfs_iterator it{ list };
	it.stack_.push_back(&list.list_.front());

	for (auto& v : list) {
		it.metadata_map_[v] = { vertex_color::white, "" };
	}

	return it;
}

dfs_iterator dfs_iterator::create_end(adjacency_list& list) {
	return dfs_iterator(list);
}

dfs_iterator::reference dfs_iterator::operator*() {
	if (stack_.empty()) {
		throw std::exception("dereferencing dfs iterator when there is no current item");
	}

	return *stack_.back();
}

dfs_iterator& dfs_iterator::operator++() {
	if (stack_.empty()) {
		throw std::exception("advancing iterator past end()");
	}

	auto* current = stack_.back();
	stack_.pop_back();

	// TODO - handle when a black vertex is popped off the stack
	for (auto& e: current->edges) {
		auto& neighbour = *e.to;
		auto& neighbour_metadata = metadata_map_[neighbour];

		if (neighbour_metadata.color == vertex_color::white) {
			stack_.push_back(&neighbour);
			neighbour_metadata.color = vertex_color::gray;
		}
	}

	metadata_map_[*current].color = vertex_color::black;

	return *this;
}

bool dfs_iterator::operator==(const dfs_iterator& rhs) const {	
	if (stack_.size() != rhs.stack_.size()) return false;
	
	// End iterators are represented by empty stacks,
	// in which case they are equal if they're based off the same
	// adjacency_list.
	if (stack_.empty() && rhs.stack_.empty()) {
		return &list_ == &rhs.list_;
	}

	// But if neither of them are empty, we simply compare the
	// stacks (at this point we know the sizes are the same.)
	assert(stack_.size() == rhs.stack_.size());
	
	auto i1 = stack_.cbegin();
	auto i2 = rhs.stack_.cbegin();

	auto e = stack_.cend();

	for (; i1 != e; ++i1, ++i2) {
		// We can compare the vertices by their address,
		// as the list is always the source of truth.
		if (&*i1 != &*i2) {
			return false;
		}
	}

	return true;
}

adjacency_list::adjacency_list(const adjacency_list& rhs): list_(rhs.list_), counter_(rhs.counter_) {
}

adjacency_list::adjacency_list(adjacency_list&& rhs) {
	counter_ = rhs.counter_;
	list_ = std::move(rhs.list_);
}

adjacency_list::~adjacency_list() {
}

adjacency_list& adjacency_list::operator=(const adjacency_list& rhs) {
	counter_ = rhs.counter_;
	list_ = rhs.list_;

	return *this;
}

adjacency_list& adjacency_list::operator=(adjacency_list&& rhs) {
	using std::swap;

	swap(*this, rhs);
	return *this;
}

dfs_iterator adjacency_list::dfs_begin() {
	return dfs_iterator::create_begin(*this);
}

dfs_iterator adjacency_list::dfs_end() {
	return dfs_iterator::create_end(*this);
}

void adjacency_list::swap(adjacency_list& rhs) {
	using std::swap;

	swap(list_, rhs.list_);
	swap(counter_, rhs.counter_);
}

vertex& adjacency_list::add() {
	list_.emplace_back(counter_++, *this);
	return list_.back();
}

vertex* adjacency_list::find_by_id(int id) {
	auto it = std::find_if(list_.begin(), list_.end(), [id](const vertex& v) {
		                        return v.id() == id;
	                        });

	if (it == list_.end()) {
		return nullptr;
	} else {
		return &*it;
	}
}

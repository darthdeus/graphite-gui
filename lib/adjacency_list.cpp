#include <algorithm>
#include <assert.h>
#include <list>
#include "adjacency_list.h"

dfs_iterator::dfs_iterator(adjacency_list& list) : list_(list) {
}

dfs_iterator dfs_iterator::create_begin(adjacency_list& list) {
	if (list.empty()) return create_end(list);

	dfs_iterator it{list};
	it.stack_.push_back(&list.list_.front());

	for (auto& v : list) {
		v.color = vertex_color::white;
		v.label = "";
	}

	return it;
}

dfs_iterator dfs_iterator::create_end(adjacency_list& list) {
	return dfs_iterator(list);
}

dfs_iterator::reference dfs_iterator::operator*() {
	if (stack_.empty()) {
		throw std::exception("dereferencing end() iterator");
	}

	return *stack_.back();
}

dfs_iterator::pointer dfs_iterator::operator->() const {
	if (stack_.empty()) {
		throw std::exception("dereferencing end() iterator");
	}

	return stack_.back();
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

		if (neighbour.color == vertex_color::white) {
			stack_.push_back(&neighbour);
			neighbour.color = vertex_color::gray;
		}
	}

	current->color = vertex_color::black;

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

	for (; i1 != e; ++i1 , ++i2) {
		// We can compare the vertices by their address,
		// as the list is always the source of truth.
		if (&*i1 != &*i2) {
			return false;
		}
	}

	return true;
}

bool dfs_iterator::operator!=(const dfs_iterator& rhs) const {
	return !(*this == rhs);
}

adjacency_list::adjacency_list(): counter_(0) {
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

auto adjacency_list::begin() -> iterator {
	return list_.begin();
}

auto adjacency_list::end() -> iterator {
	return list_.end();
}

auto adjacency_list::begin() const -> const_iterator {
	return list_.begin();
}

auto adjacency_list::end() const -> const_iterator {
	return list_.end();
}

auto adjacency_list::cbegin() const -> const_iterator {
	return list_.cbegin();
}

auto adjacency_list::cend() const -> const_iterator {
	return list_.cend();
}

dfs_iterator adjacency_list::dfs_begin() {
	return dfs_iterator::create_begin(*this);
}

dfs_iterator adjacency_list::dfs_end() {
	return dfs_iterator::create_end(*this);
}

bool adjacency_list::operator==(const adjacency_list& rhs) const {
	return list_ == rhs.list_;
}

bool adjacency_list::operator!=(const adjacency_list& rhs) const {
	return !(*this == rhs);
}

void adjacency_list::swap(adjacency_list& rhs) {
	using std::swap;

	swap(list_, rhs.list_);
	swap(counter_, rhs.counter_);
}

adjacency_list::size_type adjacency_list::size() const {
	return list_.size();
}

adjacency_list::size_type adjacency_list::max_size() const {
	return list_.max_size();
}

bool adjacency_list::empty() const {
	return list_.empty();
}

auto adjacency_list::add() -> reference {
	list_.emplace_back(counter_++, *this);
	return list_.back();
}

auto adjacency_list::find_by_id(int id) -> pointer {
	auto f = [id](const reference v) {
		return v.id() == id;
	};

	auto it = std::find_if(list_.begin(), list_.end(), f);

	if (it == list_.end()) {
		return nullptr;
	} else {
		return &*it;
	}
}

void adjacency_list::remove(reference v) {
	list_.remove(v);
}

bool adjacency_list::remove(int id) {
	auto* v = find_by_id(id);
	if (v) {
		list_.remove(*v);
		return true;
	} else {
		return false;
	}
}

void adjacency_list::connect(reference a, reference b, bool oriented) {
	a.edges.emplace_back(&a, &b);
	if (!oriented) {
		b.edges.emplace_back(&b, &a);
	}
}

bool adjacency_list::connect(int a, int b, bool oriented) {
	auto* v1 = find_by_id(a);
	auto* v2 = find_by_id(b);

	if (v1 && v2) {
		v1->edges.emplace_back(v1, v2);
		if (!oriented) {
			v2->edges.emplace_back(v2, v1);
		}

		return true;
	} else {
		return false;
	}
}

void adjacency_list::disconnect(reference a, reference b, bool oriented) {
	// The a->b direction is always removed
	{
		auto f = [b](Edge& e) {
			return e.to == &b;
		};

		auto it = std::find_if(a.edges.begin(), a.edges.end(), f);
		if (it != a.edges.end()) {
			a.edges.erase(it);
		}
	}

	// but a<-b only if the disconnect is not oriented
	if (!oriented) {
		auto f = [a](Edge& e) {
			return e.to == &a;
		};
		auto it = std::find_if(b.edges.begin(), b.edges.end(), f);
		if (it != b.edges.end()) {
			b.edges.erase(it);
		}
	}
}

bool adjacency_list::disconnect(int a, int b, bool oriented) {
	auto* v1 = find_by_id(a);
	auto* v2 = find_by_id(b);

	if (v1 && v2) {
		disconnect(*v1, *v2, oriented);
		return true;
	} else {
		return false;
	}
}
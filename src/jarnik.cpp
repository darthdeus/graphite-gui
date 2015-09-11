#include <assert.h>
#include "jarnik.h"
#include "graph.h"
#include "vertex.h"
#include "logger.h"

Jarnik::Jarnik(Graph& g, Vertex& start) : g_(g), start_(&start) {}

void Jarnik::start() {
  start_->color = vertex_color::gray;
  queue_ = decltype(queue_)();

  for (auto& v : g_) {
    v.label = "";

    for (auto& e : v.edges) {
      e.deleted = false;
      e.oriented = false;
      e.weighted = true;
      e.bridge = false;
    }
  }

  for (Edge& e : start_->edges) {
    queue_.push(&e);
  }
}

void Jarnik::step() {
  if (queue_.empty()) {
    event_log << "trying to step over a finished algorithm";

    for (auto& v : g_) {
      v.color = vertex_color::black;

      for (auto& e : v.edges) {
        if (!e.bridge) e.deleted = true;
      }
    }

    return;
  }

  Edge* current = queue_.top();
  queue_.pop();
  assert(current);

  current->from->color = vertex_color::black;

  Vertex* to = current->to;

  if (to->color != vertex_color::white) {
    event_log << "ignoring open vertex";
    return;
  }

  // The spanning tree edges are marked as bridges, which is purely
  // for rendering purposes (bridges are colored red.)
  current->bridge = true;
  current->reverseEdge()->bridge = true;
  to->color = vertex_color::gray;

  for (Edge& e : to->edges) {
    if (!e.bridge) {
      queue_.push(&e);
    }
  }
}

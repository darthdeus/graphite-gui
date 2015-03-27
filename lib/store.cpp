#include <iostream>
#include <string>
#include <fstream>

#include "lib/store.hpp"
#include "lib/graph.hpp"

void store::save(const Graph& g, const std::string filename) {
  std::ofstream fs(filename);

  for (auto& v : g.list) {
    fs << *v.get() << std::endl;
  }
}

Graph store::load(const std::string filename) {
  Graph g;

  std::ifstream fs(filename);
  // fs >> 
  // TODO - figure out what to do with this

  return std::move(g);
}

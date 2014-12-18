#include <iostream>
#include <string>
#include <fstream>

#include "lib/store.hpp"
#include "lib/graph.hpp"

void store::save(const graph& g, const std::string filename) {
  std::ofstream fs(filename);

  for (auto& v : g.list) {
    fs << *v.get() << std::endl;
  }
}

graph store::load(const std::string filename) {
  graph g;

  std::ifstream fs(filename);
  // fs >> 

  return std::move(g);
}

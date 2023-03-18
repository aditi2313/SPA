#include "Utility.h"

namespace util {

template <class Node, class Container = std::vector<Node>>
void GraphSearch<Node, Container>::BFS(
    std::function<Container(Node &)> get_children,
    const Container intial_children,
    std::function<bool(const Node &)> add_result) {
  std::queue<Node> frontier;
  std::unordered_set<Node> visited;
  for (auto &node : intial_children) {
    frontier.push(node);
  }
  while (!frontier.empty()) {
    auto &c = frontier.front();
    frontier.pop();
    if (visited.count(c)) {
      continue;
    }
    visited.insert(c);
    if (!add_result(c)) {
      continue;
    }

    for (auto &v : get_children(c)) {
      frontier.push(v);
    }
  }
}
}  // namespace util
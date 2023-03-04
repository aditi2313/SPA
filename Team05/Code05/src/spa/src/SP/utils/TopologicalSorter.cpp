#include "TopologicalSorter.h"

namespace sp {
std::vector<std::string> TopologicalSorter::Sort(
    std::unordered_map<std::string, std::unordered_set<std::string>>&
        called_by) {
  // Calculate number of incoming edges for each procedure where there is an
  // edge from A to B if A is called by B
  std::unordered_map<std::string, int> num_incoming_edges;
  for (auto& [key, value] : called_by) {
    // initialise to 0 incoming edges
    num_incoming_edges[key] = 0;
  }
  for (auto& [key, value] : called_by) {
    for (auto& direct_call : value) {
      num_incoming_edges[direct_call]++;
    }
  }

  // Initialise queue with procedures that have 0 incoming edges
  std::queue<std::string> queue;
  for (auto& [key, value] : num_incoming_edges) {
    if (value == 0) {
      queue.push(key);
    }
  }

  std::vector<std::string> topological_ordering;
  while (!queue.empty()) {
    auto current_proc = queue.front();
    queue.pop();
    topological_ordering.push_back(current_proc);

    for (auto& caller : called_by[current_proc]) {
      num_incoming_edges[caller]--;
      if (num_incoming_edges[caller] == 0) {
        queue.push(caller);
      }
    }
  }

  return topological_ordering;
}
}  // namespace sp

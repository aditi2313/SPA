#include "ClauseOptimiser.h"

#include <queue>

namespace qps {
std::vector<ClauseOptimiser::Group> ClauseOptimiser::GroupClauses(
    std::vector<ClausePtr> &clauses) {
  AdjList adj_list;
  PreprocessClauses(clauses, adj_list);
  std::vector<ClauseOptimiser::Group> groups;

  int N = clauses.size();
  std::vector<bool> visited(N, false);
  for (int i = 0; i < N; ++i) {
    if (visited[i]) continue;

    // Start a new group and perform a BFS on i
    groups.emplace_back(ClauseOptimiser::Group());
    BFS(i, adj_list, visited, groups.back());
  }

  return groups;
}

void ClauseOptimiser::BFS(
    int source, AdjList &AL, std::vector<bool> &visited, Group &group) {
  std::queue<int> q;
  q.push(source);
  visited[source] = true;

  while (!q.empty()) {
    int curr = q.front();
    q.pop();
    group.emplace_back(curr);  // Add to current group

    for (int neigh : AL.at(curr)) {
      if (!visited[neigh]) q.push(neigh);
      visited[neigh] = true;
    }
  }
}

void ClauseOptimiser::PreprocessClauses(
    std::vector<ClausePtr> &clauses, AdjList &adj_list) {
  int num_clauses = clauses.size();
  adj_list.assign(num_clauses, std::vector<int>());
  for (int i = 0; i < num_clauses; ++i) {
    for (int j = 0; j < i; ++j) {
      if (SharesSynonym(clauses.at(i), clauses.at(j))) {
        // Draw a bidirectional edge between i and j
        adj_list.at(i).emplace_back(j);
        adj_list.at(j).emplace_back(i);
      }
    }
  }
}

// Given two clauses, return true if they share at least one same
// synonym as an argument and false otherwise.
bool ClauseOptimiser::SharesSynonym(ClausePtr &LHS, ClausePtr &RHS) {
  // Four comparisons to be made
  if (LHS->arg1_->IsSynonym()) {
    if (*LHS->arg1_ == *RHS->arg1_) return true;
    if (*LHS->arg1_ == *RHS->arg2_) return true;
  }
  if (LHS->arg2_->IsSynonym()) {
    if (*LHS->arg2_ == *RHS->arg1_) return true;
    if (*LHS->arg2_ == *RHS->arg2_) return true;
  }
  return false;
}
}  // namespace qps

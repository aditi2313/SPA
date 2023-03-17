#pragma once

#include <vector>

#include "QPS/models/Query.h"

namespace qps {
class ClauseOptimiser {
 public:
  // Adjacency list
  using AdjList = std::vector<std::vector<int>>;
  // A group is a list of indexes of clauses in that same group
  using Group = std::vector<int>;

  // Returns a list of groups
  std::vector<Group> GroupClauses(std::vector<ClausePtr> &clauses);

 private:
  // Given a list of clauses, iterate through each
  // clause and find clauses that it shares at least
  // one synonym argument with.
  // Update adj_list by drawing a bidirectional edge
  // between these two clause indexes.
  void PreprocessClauses(std::vector<ClausePtr> &clauses, AdjList &adj_list);

  // Given two clauses, return true if they share at least one same
  // synonym as an argument and false otherwise.
  bool SharesSynonym(ClausePtr &LHS, ClausePtr &RHS);

  // Starts a BFS from `source` and using `AL`.
  // Adds all nodes visited on the BFS to `group`
  // as they belong to the same `group`.
  // Implicitly the order of nodes being added to `group` also ensures that
  // during QueryEvaluation, processing a new Clause has a shared synonym (edge)
  // to a Clause that has been previously processed, hence avoiding expensive
  // cross products.
  void BFS(int source, AdjList &AL, std::vector<bool> &visited, Group &group);
};
}  // namespace qps

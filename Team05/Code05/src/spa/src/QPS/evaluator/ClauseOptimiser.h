#pragma once

#include <vector>

#include "QPS/models/Query.h"

namespace qps {
class ClauseOptimiser {
 public:
  // Adjacency List
  using AdjList = std::vector<std::vector<int>>;
  // A group is a list of indexes of clauses
  using Group = std::vector<int>;

  static std::vector<Group> &GroupClauses(std::vector<ClausePtr> &clauses);

 private:
  static void PreprocessClauses(
      std::vector<ClausePtr> &clauses, AdjList &adj_list);
  static bool SharesSynonym(ClausePtr &LHS, ClausePtr &RHS);
  static void BFS(
      int source, AdjList &AL, std::vector<bool> &visited, Group &group);
};
}  // namespace qps

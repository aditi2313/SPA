#pragma once

#include <vector>
#include <unordered_set>

#include "QPS/models/Table.h"

namespace qps {
class TableJoiner {
 public:
  static Table Join(Table &LHS, Table &RHS);

  static std::unordered_set<SynonymName> IntersectColumns(
      std::vector<SynonymName> &LHS,
      std::vector<SynonymName> &RHS);

 private:
  static Table Intersect(
      Table &LHS,
      Table &RHS,
      std::unordered_set<SynonymName> &join_cols);

  static Table CrossProduct(Table &LHS, Table &RHS);

  static std::vector<SynonymName> UnionColumns(
      std::vector<SynonymName> &LHS,
      std::vector<SynonymName> &RHS);
};
}  // namespace qps

#pragma once

#include <vector>

#include "QPS/models/Table.h"

namespace qps {
class TableJoiner {
 public:
  static Table Join(Table &LHS, Table &RHS);

  static std::vector<SynonymName> IntersectColumns(
	  std::vector<SynonymName> &LHS,
	  std::vector<SynonymName> &RHS);

 private:
  static Table Intersect(
      Table &LHS,
      Table &RHS,
      std::vector<SynonymName> &join_cols);

  static Table CrossProduct(Table &LHS, Table &RHS);

  static std::vector<SynonymName> UnionColumns(
      std::vector<SynonymName> &LHS,
      std::vector<SynonymName> &RHS);
};
}  // namespace qps

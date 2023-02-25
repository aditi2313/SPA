#include "TableJoiner.h"

namespace qps {

// TODO(JL): Can be optimized more in terms of time complexity
Table TableJoiner::Join(Table &LHS, Table &RHS) {
  auto join_columns = IntersectColumns(LHS.get_columns(), RHS.get_columns());
  auto new_columns = UnionColumns(
      LHS.get_columns(), RHS.get_columns());
  Table new_table(new_columns);

  for (int i = 0, N1 = LHS.Size(); i < N1; ++i) {
    for (int j = 0, N2 = RHS.Size(); j < N2; ++j) {
      bool should_join = true;
      for (auto col : join_columns) {
        if (LHS.Index(i, col) != RHS.Index(j, col)) {
          should_join = false;
          break;
        }
      }

      if (!should_join) continue;

      Table::Row new_row;

      for (auto col : new_columns) {
        if (LHS.HasColumn(col)) {
          new_row.emplace_back(
              col, LHS.Index(i, col));
        } else {
          new_row.emplace_back(
              col, RHS.Index(j, col));
        }
      }

      new_table.AddRow(new_row);
    }
  }

  return new_table;
}

std::vector<SynonymName> TableJoiner::UnionColumns(
    std::vector<SynonymName> &LHS,
    std::vector<SynonymName> &RHS) {
  std::unordered_set<SynonymName> cols_set;
  for (auto col : LHS) {
    cols_set.insert(col);
  }
  for (auto col : RHS) {
    cols_set.insert(col);
  }
  return std::vector<SynonymName>(
      cols_set.begin(), cols_set.end());
}

std::vector<SynonymName> TableJoiner::IntersectColumns(
    std::vector<SynonymName> &LHS,
    std::vector<SynonymName> &RHS) {
  std::unordered_set<SynonymName> cols_set;
  std::vector<SynonymName> results;
  for (auto col : LHS) {
    cols_set.insert(col);
  }
  for (auto col : RHS) {
    if (cols_set.count(col)) {
      results.push_back(col);
    }
  }
  return results;
}
}

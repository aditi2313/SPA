#include "TableJoiner.h"

#include <unordered_set>
#include <vector>

namespace qps {
// Join two tables on common columns
// For example, if LHS and RHS share the two columns
// Synonym "a" and Synonym "v",
// the new table contains all the rows where the values
// for "a" and "v" for LHS and RHS are the same.
// If there are no common columns, the result is
// essentially the cross product of the two tables.
Table TableJoiner::Join(Table &LHS, Table &RHS) {
  auto join_columns = IntersectColumns(
      LHS.get_columns(), RHS.get_columns());
  if (join_columns.empty()) {
    return CrossProduct(LHS, RHS);
  } else {
    return Intersect(LHS, RHS, join_columns);
  }
}

Table TableJoiner::CrossProduct(Table &LHS, Table &RHS) {
  auto new_columns = UnionColumns(
      LHS.get_columns(), RHS.get_columns());
  Table new_table(new_columns);

  for (int i = 0, N1 = LHS.Size(); i < N1; ++i) {
    for (int j = 0, N2 = RHS.Size(); j < N2; ++j) {
      Table::Row new_row;

      for (auto &col : new_columns) {
        LHS.HasColumn(col)
        ? new_row.emplace_back(
            col, LHS.Index(i, col))
        : new_row.emplace_back(
            col, RHS.Index(j, col));
      }

      new_table.add_row(new_row);
    }
  }

  return new_table;
}

// TODO(JL): Can be optimized further in terms of time complexity
Table TableJoiner::Intersect(
    Table &LHS, Table &RHS, std::vector<SynonymName> &join_columns) {
  auto new_columns = UnionColumns(
      LHS.get_columns(), RHS.get_columns());

  Table new_table(new_columns);

  for (int i = 0, N1 = LHS.Size(); i < N1; ++i) {
    for (int j = 0, N2 = RHS.Size(); j < N2; ++j) {
      bool should_join = true;
      for (auto &col : join_columns) {
        should_join &= LHS.Index(i, col) == RHS.Index(j, col);
      }

      if (!should_join) continue;

      Table::Row new_row;

      for (auto &col : new_columns) {
        LHS.HasColumn(col)
        ? new_row.emplace_back(
            col, LHS.Index(i, col))
        : new_row.emplace_back(
            col, RHS.Index(j, col));
      }

      new_table.add_row(new_row);
    }
  }

  return new_table;
}

// Given two list of columns, return a list of columns
// that is the union of all the column names that
// appear in either list
std::vector<SynonymName> TableJoiner::UnionColumns(
    std::vector<SynonymName> &LHS,
    std::vector<SynonymName> &RHS) {
  std::unordered_set<SynonymName> cols_set;
  for (auto &col : LHS) {
    cols_set.insert(col);
  }
  for (auto &col : RHS) {
    cols_set.insert(col);
  }
  return std::vector<SynonymName>(
      cols_set.begin(), cols_set.end());
}

// Given two list of columns, return a list of columns
// that is the intersection of all the column names that
// must appear in both lists
std::vector<SynonymName> TableJoiner::IntersectColumns(
    std::vector<SynonymName> &LHS,
    std::vector<SynonymName> &RHS) {
  std::unordered_set<SynonymName> cols_set;
  std::vector<SynonymName> results;
  for (auto &col : LHS) {
    cols_set.insert(col);
  }
  for (auto &col : RHS) {
    if (cols_set.count(col)) {
      results.push_back(col);
    }
  }
  return results;
}
}  // namespace qps

#include "TableJoiner.h"

#include <unordered_set>
#include <unordered_map>
#include <vector>

namespace qps {

std::unordered_set<SynonymName> IntersectCols(std::vector<SynonymName> &LHS,
                                              std::vector<SynonymName> &RHS);
// Join two tables on common columns
// For example, if LHS and RHS share the two columns
// Synonym "a" and Synonym "v",
// the new table contains all the rows where the values
// for "a" and "v" for LHS and RHS are the same.
// If there are no common columns, the result is
// essentially the cross product of the two tables.
Table TableJoiner::Join(Table &LHS, Table &RHS) {
  if (!LHS.is_initialized_) return RHS;
  if (!RHS.is_initialized_) return LHS;

  auto join_columns = IntersectCols(
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
    Table &LHS, Table &RHS, std::unordered_set<SynonymName> &join_columns) {
  auto new_columns = UnionColumns(LHS.get_columns(), RHS.get_columns());
  std::unordered_map<Table::RowEntity, std::vector<int>> row_map;
  Table new_table(new_columns);
  auto &smaller_table = LHS.Size() < RHS.Size() ? LHS : RHS;
  auto &larger_table = LHS.Size() < RHS.Size() ? RHS : LHS;

  for (int i = 0, N1 = smaller_table.Size(); i < N1; ++i) {
    Table::RowEntity row;
    for (auto &syn : join_columns) {
      row.push_back(smaller_table.Index(i, syn));
    }
    row_map[row].push_back(i);
  }

  // TODO(Gab) POD lel
  for (int i = 0, N2 = larger_table.Size(); i < N2; ++i) {
    Table::RowEntity row;
    for (auto &syn : join_columns) {
      row.push_back(larger_table.Index(i, syn));
    }
    if (!row_map.count(row)) continue;
    Table::Row new_row;
    auto &rows = row_map.at(row);
    for (auto &j : join_columns) {
      new_row.emplace_back(j, larger_table.Index(i, j));
    }
    for (auto &r : rows) {
      Table::Row new_row_inner = new_row;
      int ctr = -1;
      for (auto &inner_col : smaller_table.get_columns()) {
        ctr++;
        if (join_columns.count(inner_col)) continue;
        new_row_inner.emplace_back(inner_col,
          smaller_table.Index(r, inner_col));
      }
      for (auto &col : larger_table.get_columns()) {
        if (join_columns.count(col)) continue;
        new_row_inner.emplace_back(col, larger_table.Index(i, col));
      }
      new_table.add_row(new_row_inner);
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

// TODO(Gab) DRY
std::unordered_set<SynonymName> IntersectCols(std::vector<SynonymName> &LHS,
    std::vector<SynonymName> &RHS) {
  std::unordered_set<SynonymName> cols_set;
  std::unordered_set<SynonymName> results;
  for (auto &col : LHS) {
    cols_set.insert(col);
  }
  for (auto &col : RHS) {
    if (cols_set.count(col)) {
      results.insert(col);
    }
  }
  return results;
}

}  // namespace qps

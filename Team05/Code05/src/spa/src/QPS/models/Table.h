#pragma once

#include <unordered_map>
#include <unordered_set>
#include <set>
#include <utility>
#include <vector>
#include <iostream>

#include "Synonym.h"

namespace qps {
class Table {
 public:
  using Row = std::vector<std::pair<SynonymName, Entity>>;
  using TwoSynonymRows = std::vector<std::pair<Entity, Entity>>;
  using RowEntity = std::vector<Entity>;
  friend class TableJoiner;

  // Empty constructor.
  Table() {}

  // Initialize table with one column filled with
  // Entities
  Table(SynonymName syn_name, EntitySet &entities) {
    int id = columns_.size();
    id_map_[syn_name] = id;
    columns_.push_back(syn_name);
    columns_set_.insert(syn_name);
    for (auto &entity : entities) {
      rows_.push_back(std::vector<Entity>());
      rows_.back().push_back(entity);
    }
  }

  // Initialize table with columns but no entities
  explicit Table(std::vector<SynonymName> &columns) {
    int id = 0;
    columns_ = columns;
    for (auto col : columns) {
      id_map_[col] = id++;
      columns_set_.insert(col);
    }
  }

  inline bool Empty() {
    return rows_.empty();
  }

  inline int Size() {
    return rows_.size();
  }

  inline Entity Index(int row, SynonymName col) {
    return rows_.at(row).at(id_map_.at(col));
  }

  inline const RowEntity& Index(int row) { return rows_.at(row); }

  inline std::vector<SynonymName> &get_columns() {
    return columns_;
  }

  inline void add_row(const RowEntity &row) { rows_.push_back(row); }

  inline void add_values(SynonymName column, EntitySet &values) {
    for (auto &value : values) {
      Row new_row;
      new_row.emplace_back(column, value);
      add_row(new_row);
    }
  }

  inline void add_values(
      SynonymName col1, SynonymName col2,
      std::vector<std::pair<Entity, Entity>> &values) {
    for (auto &[lhs, rhs] : values) {
      Row new_row;
      new_row.emplace_back(col1, lhs);
      new_row.emplace_back(col2, rhs);
      add_row(new_row);
    }
  }

  inline bool HasColumn(SynonymName syn_name) {
    return columns_set_.count(syn_name);
  }

  inline void Select(
      std::vector<SynonymName> columns,
      std::vector<std::vector<Entity>> &results) {
    std::set<std::vector<Entity>> seen;

    for (auto &arr : rows_) {
      std::vector<Entity> new_row;
      for (auto col : columns) {
        new_row.emplace_back(arr[id_map_.at(col)]);
      }
      // Already added
      if (seen.count(new_row)) { continue; }

      // Add to results
      results.emplace_back(new_row);
      seen.insert(new_row);
    }
  }

  void PrintDebug();

 private:
  inline void add_row(Row &row) {
    std::vector<Entity> new_row(columns_.size());
    for (auto [syn, entity] : row) {
      new_row.at(id_map_.at(syn)) = entity;
    }
    rows_.emplace_back(new_row);
  }  
  std::vector<SynonymName> columns_;
  std::unordered_set<SynonymName> columns_set_;  // for O(1) HasColumn
  std::unordered_map<SynonymName, int> id_map_;
  std::vector<std::vector<Entity>> rows_;
};
}  // namespace qps

template <>
class std::hash<qps::Table::RowEntity> {
 public:
  std::size_t operator()(const qps::Table::RowEntity row) const {
    std::size_t result = 0;
    for (auto &val : row) {
      result ^= std::hash<qps::Entity>{}(val) + 0x9e3779b9 + (result << 6) +
                (result >> 2);
    }
    return result;
  }
};


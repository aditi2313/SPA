#pragma once

#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "Synonym.h"

namespace qps {
class Table {
 public:
  using Row = std::vector<std::pair<SynonymName, Entity>>;

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

  inline std::vector<SynonymName> &get_columns() {
    return columns_;
  }

  inline bool HasColumn(SynonymName syn_name) {
    return columns_set_.count(syn_name);
  }

  inline EntitySet Select(SynonymName syn_name) {
    EntitySet results;

    int index = id_map_.at(syn_name);
    for (auto &arr : rows_) {
      results.insert(arr.at(index));
    }
    return results;
  }

  inline void AddRow(Row &row) {
    std::vector<Entity> new_row(columns_.size());
    for (auto [syn, entity] : row) {
      new_row.at(id_map_.at(syn)) = entity;
    }
    rows_.emplace_back(new_row);
  }

  void PrintDebug();

 private:
  std::vector<SynonymName> columns_;
  std::unordered_set<SynonymName> columns_set_;  // for O(1) HasColumn
  std::unordered_map<SynonymName, int> id_map_;
  std::vector<std::vector<Entity>> rows_;
};
}  // namespace qps

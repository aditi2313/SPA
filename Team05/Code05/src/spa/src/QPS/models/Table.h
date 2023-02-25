#pragma once

#include <unordered_map>
#include <vector>

#include "Synonym.h"

namespace qps {
class Table {
 public:
  // Empty constructor.
  Table() {}

  Table(SynonymName syn_name, EntitySet &entities) {
    int id = columns_.size();
    id_map_[syn_name] = id;
    columns_.push_back(syn_name);
    for (auto &entity : entities) {
      rows_.push_back(std::vector<Entity>());
      rows_.back().push_back(entity);
    }
  }

  inline bool Empty() {
    return rows_.empty();
  }

  inline EntitySet Select(SynonymName syn_name) {
    EntitySet results;

    int index = id_map_.at(syn_name);
    for (auto &arr : rows_) {
      results.insert(arr.at(index));
    }
    return results;
  }

  inline void AddRow() {
    // TODO(JL)
  }
  // Methods to create:
  // CrossProduct
  // Join
  // Select

 private:
  std::vector<SynonymName> columns_;
  std::unordered_map<SynonymName, int> id_map_;
  std::vector<std::vector<Entity>> rows_;
};
}  // namespace qps

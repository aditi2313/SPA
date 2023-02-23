#pragma once

#include <unordered_map>
#include <iostream>

#include "Synonym.h"

namespace qps {
class Table {
 public:
  // Empty constructor.
  Table() {}

  Table(SynonymName syn_name, EntityPtrList &entities) {
    int id = data_.size();
    id_map_[syn_name] = id;
    columns_.push_back(syn_name);
    data_.push_back(EntityPtrList());
    for (auto &entity : entities) {
      data_.at(id).push_back(entity->Copy());
    }
  }

  inline bool Empty() {
    return data_.empty();
  }

  inline EntityPtrList &Select(SynonymName syn_name) {
    return data_.at(id_map_.at(syn_name));
  }
  // Methods to create:
  // CrossProduct
  // Join
  // Select

 private:
  std::vector<SynonymName> columns_;
  std::unordered_map<SynonymName, int> id_map_;
  std::vector<EntityPtrList> data_;
};
}  // namespace qps
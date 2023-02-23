#pragma once

#include <vector>
#include <utility>
#include <memory>

#include "models/Entity.h"
#include "models/types.h"

using models::EntityPtrList;
using models::EntityName;
using models::SynonymName;

namespace qps {
class Synonym {
 public:
  Synonym(SynonymName syn_name, EntityName entity_name) :
      syn_name_(syn_name), entity_name_(entity_name) {}

  inline SynonymName get_syn_name() const {
    return syn_name_;
  }

  inline EntityName get_entity_name() const {
    return entity_name_;
  }

  inline EntityPtrList &get_possible_entities() {
    return possible_entities_;
  }

  inline void set_possible_entities(EntityPtrList &entities) {
    possible_entities_.clear();
    for (auto &entity : entities) {
      possible_entities_.push_back(std::move(entity));
    }
  }

  inline bool operator==(const Synonym &other) const {
    return syn_name_ == other.syn_name_
        && entity_name_ == other.entity_name_;
  }

  inline bool operator!=(const Synonym &other) const {
    return !(*this == other);
  }

 private:
  SynonymName syn_name_;
  EntityName entity_name_;
  EntityPtrList possible_entities_;
};

using SynonymPtr = std::unique_ptr<Synonym>;
}  // namespace qps

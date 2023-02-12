#pragma once

#include <vector>

#include "models/Entity.h"
#include "models/types.h"

using models::EntityPtrList;
using models::EntityName;
using models::SynonymName;

namespace qps {
class Synonym {
 public:
  Synonym(SynonymName syn_id, EntityName entity_name) :
      syn_id_(syn_id), entity_name_(entity_name) {}

  inline SynonymName get_syn_id() const {
    return syn_id_;
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
    return syn_id_ == other.syn_id_
        && entity_name_ == other.entity_name_;
  }

  inline bool operator!=(const Synonym &other) const {
    return !(*this == other);
  }

 private:
  SynonymName syn_id_;
  EntityName entity_name_;
  EntityPtrList possible_entities_;
};

using SynonymPtr = std::unique_ptr<Synonym>;
}  // namespace qps



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
  Synonym(SynonymName syn_id, EntityName entity_id) :
    syn_id_(syn_id), entity_id_(entity_id) {}

  inline SynonymName get_syn_id() const {
    return syn_id_;
  }

  inline EntityName get_entity_id() const {
    return entity_id_;
  }

  inline EntityPtrList &get_possible_entities() {
    return possible_entities_;
  }

  inline void set_possible_entities(EntityPtrList entities) {
    possible_entities_.clear();
    for (auto &entity : entities) {
      possible_entities_.push_back(std::move(entity));
    }
  }

  inline bool operator==(const Synonym &other) const {
    return syn_id_ == other.syn_id_
    && entity_id_ == other.entity_id_;
  }

  inline bool operator!=(const Synonym &other) const {
    return !(*this == other);
  }


 private:
  SynonymName syn_id_;
  EntityName entity_id_;
  EntityPtrList possible_entities_;
};

using SynonymPtr = std::unique_ptr<Synonym>;
}  // namespace qps



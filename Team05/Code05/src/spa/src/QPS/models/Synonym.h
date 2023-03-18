#pragma once

#include <vector>
#include <utility>
#include <memory>

#include "Entity.h"
#include "models/types.h"

namespace qps {
class Synonym {
 public:
  Synonym(SynonymName syn_name, EntityType entity_type) :
      syn_name_(syn_name), entity_type_(entity_type) {}

  inline SynonymName get_syn_name() const {
    return syn_name_;
  }

  inline EntityType get_entity_name() const {
    return entity_type_;
  }

  inline bool operator==(const Synonym &other) const {
    return syn_name_ == other.syn_name_
        && entity_type_ == other.entity_type_;
  }

  inline bool operator!=(const Synonym &other) const {
    return !(*this == other);
  }

 private:
  SynonymName syn_name_;
  EntityType entity_type_;
};

using SynonymPtr = std::unique_ptr<Synonym>;
}  // namespace qps

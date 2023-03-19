#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "QPS/models/clauses/Export.h"
#include "common/exceptions/QPSExceptions.h"

namespace qps {
class ClauseFactory {
 public:
  ClauseFactory() {}
  virtual ClausePtr Create(ArgumentPtr arg1, ArgumentPtr arg2) = 0;

  inline virtual bool Validate(ArgumentPtr &arg1, ArgumentPtr &arg2) {
    if (!is_wildcard_allowed_as_first_arg_ && arg1->IsWildcard()) {
      return false;
    }

    return arg1->Validate(LHS_entity_types_) &&
           arg2->Validate(RHS_entity_types_);
  }

  virtual ~ClauseFactory() = default;

 protected:
  void InitializeWildcard(ArgumentPtr &arg, EntityType entity_type) {
    if (!arg->IsWildcard()) return;
    Wildcard *wildcard = dynamic_cast<Wildcard *>(arg.get());
    wildcard->set_entity_type(entity_type);
  }

  std::unordered_set<EntityType> LHS_entity_types_;
  std::unordered_set<EntityType> RHS_entity_types_;
  bool is_wildcard_allowed_as_first_arg_ = true;
};
}  // namespace qps

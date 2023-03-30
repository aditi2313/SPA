#pragma once

#include <string>
#include <variant>
#include <unordered_set>

#include "Data.h"
#include "Types.h"

namespace pkb {
class ConditionData : public Data<Key>{
 public:
  ConditionData(
          Key line,
      const StringSet &variable_names);

  friend bool operator<(const ConditionData& LHS, const ConditionData& RHS) {
    return LHS.line_ < RHS.line_ ||
        (LHS.line_ == RHS.line_ &&
            std::lexicographical_compare(LHS.variable_names_.begin(),
                                         LHS.variable_names_.end(),
                                         RHS.variable_names_.begin(),
                                         RHS.variable_names_.end()));
  }

  friend bool operator==(const ConditionData& LHS, const ConditionData& RHS) {
    return LHS.line_ == RHS.line_ &&
           LHS.variable_names_ == RHS.variable_names_;
  }

  inline const StringSet& get_variables() const {
    return variable_names_;
  }

 private:
  // Variable names that appear in the condition
  StringSet variable_names_;
};
}  // namespace pkb

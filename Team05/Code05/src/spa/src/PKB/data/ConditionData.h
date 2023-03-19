#pragma once

#include <string>
#include <variant>
#include <unordered_set>

#include "Data.h"

namespace pkb {
class ConditionData : public Data<std::variant<int, std::string>>{
 public:
  ConditionData(
      std::variant<int, std::string> line,
      const std::unordered_set<std::string> &variable_names);

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

  inline const std::unordered_set<std::string>& get_variables() {
    return variable_names_;
  }

 private:
  // Variable names that appear in the condition
  std::unordered_set<std::string> variable_names_;
};
}  // namespace pkb

#pragma once

#include <string>
#include <variant>
#include <unordered_set>

namespace pkb {
class ConditionData {
 public:
  ConditionData(
      std::variant<int, std::string> line,
      const std::unordered_set<std::string> &control_variable_names);

  friend bool operator<(const ConditionData& LHS, const ConditionData& RHS) {
    return LHS.line_ < RHS.line_ ||
        (LHS.line_ == RHS.line_ &&
            std::lexicographical_compare(LHS.control_variable_names_.begin(),
                                         LHS.control_variable_names_.end(),
                                         RHS.control_variable_names_.begin(),
                                         RHS.control_variable_names_.end()));
  }

  friend bool operator==(const ConditionData& LHS, const ConditionData& RHS) {
    return LHS.line_ == RHS.line_ &&
        LHS.control_variable_names_ == RHS.control_variable_names_;
  }

  inline std::variant<int, std::string> get_index() { return line_; }

  inline const std::unordered_set<std::string>& get_control_variables() {
    return control_variable_names_;
  }

 private:
  std::variant<int, std::string> line_;
  std::unordered_set<std::string> control_variable_names_;
};

}
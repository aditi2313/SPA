#pragma once
#include <iostream>
#include <string>
#include <unordered_set>
#include <variant>

namespace pkb {

class UsesData {
 public:
  UsesData(std::variant<int, std::string> line,
           const std::unordered_set<std::string>& variable_names);

  friend bool operator<(const UsesData& LHS, const UsesData& RHS) {
    return LHS.line_ < RHS.line_ ||
           (LHS.line_ == RHS.line_ &&
            std::lexicographical_compare(
                LHS.variable_names_.begin(), LHS.variable_names_.end(),
                RHS.variable_names_.begin(), RHS.variable_names_.end()));
  }

  friend bool operator==(const UsesData& LHS, const UsesData& RHS) {
    return LHS.line_ == RHS.line_ && LHS.variable_names_ == RHS.variable_names_;
  }

  inline std::variant<int, std::string> get_index() { return line_; }

  inline void add_variables(std::unordered_set<std::string> vars) {
    variable_names_.merge(vars);
  }

  inline const std::unordered_set<std::string>& get_variables() {
    return variable_names_;
  }

 private:
  std::variant<int, std::string> line_;
  std::unordered_set<std::string> variable_names_;
};
}  // namespace pkb

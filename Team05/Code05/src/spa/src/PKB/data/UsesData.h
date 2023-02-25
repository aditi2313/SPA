#pragma once
#include <string>
#include <iostream>
#include <unordered_set>


namespace pkb {

class UsesData {
 public:
  UsesData(int line, const std::unordered_set<std::string>& variable_names);
  friend bool operator<(const UsesData& LHS, const UsesData& RHS) {
    return LHS.line_ < RHS.line_ ||
        (LHS.line_ == RHS.line_ &&
            std::lexicographical_compare(LHS.variable_names_.begin(),
                                         LHS.variable_names_.end(),
                                         RHS.variable_names_.begin(),
                                         RHS.variable_names_.end()));
  }

  friend bool operator==(const UsesData& LHS, const UsesData& RHS) {
    return LHS.line_ == RHS.line_ &&
        LHS.variable_names_ == RHS.variable_names_;
  }

  inline int get_line() { return line_; }

  inline const std::unordered_set<std::string>& get_variables() {
    return variable_names_;
  }

 private:
  int line_;
  std::unordered_set<std::string> variable_names_;
};
}  // namespace pkb
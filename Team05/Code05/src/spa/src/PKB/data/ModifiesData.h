#pragma once
#include <iostream>
#include <string>
#include <unordered_set>
#include <variant>

namespace pkb {
class ModifiesData {
 public:
  ModifiesData(std::variant<int, std::string> line,
               const std::unordered_set<std::string>& variables);
  friend bool operator<(const ModifiesData& LHS, const ModifiesData& RHS) {
    return LHS.line_ < RHS.line_ ||
        (LHS.line_ == RHS.line_ &&
        std::lexicographical_compare(LHS.variables_.begin(),
                                     LHS.variables_.end(),
                                     RHS.variables_.begin(),
                                     RHS.variables_.end()));
  }

  friend bool operator==(const ModifiesData& LHS, const ModifiesData& RHS) {
    return LHS.line_ == RHS.line_ && LHS.variables_ == RHS.variables_;
  }

  inline std::variant<int, std::string> get_index() { return line_; }

  inline const std::unordered_set<std::string>& get_variables() {
      return variables_;
  }

 private:
  std::variant<int, std::string> line_;
  std::unordered_set<std::string> variables_;
};
}  // namespace pkb

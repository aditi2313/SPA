#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "models/EntityStub.h"

namespace pkb {
class ModifiesData {
 public:
  ModifiesData(int line, const std::vector<std::string>& variables);
  friend bool operator<(const ModifiesData& LHS, const ModifiesData& RHS) {
    return LHS.line_ < RHS.line_ ||
           (LHS.line_ == RHS.line_ && LHS.variables_ < RHS.variables_);
  }

  friend bool operator==(const ModifiesData& LHS, const ModifiesData& RHS) {
    return LHS.line_ == RHS.line_ && LHS.variables_ == RHS.variables_;
  }

  inline int get_line() { return line_; }
  inline const std::vector<std::string>& get_variables() { return variables_; }

 private:
  int line_;
  std::vector<std::string> variables_;
};
}  // namespace pkb

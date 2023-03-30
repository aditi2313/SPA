#pragma once
#include <iostream>
#include <string>
#include <unordered_set>
#include <variant>

#include "Data.h"
#include "Types.h"

namespace pkb {
class ModifiesData : public Data<Key>{
 public:
  ModifiesData(Key line,
               const StringSet& variables);
  friend bool operator<(const ModifiesData& LHS, const ModifiesData& RHS) {
    return LHS.line_ < RHS.line_ ||
           (LHS.line_ == RHS.line_ &&
            std::lexicographical_compare(
                LHS.variables_.begin(), LHS.variables_.end(),
                RHS.variables_.begin(), RHS.variables_.end()));
  }

  friend bool operator==(const ModifiesData& LHS, const ModifiesData& RHS) {
    return LHS.line_ == RHS.line_ &&
           LHS.variables_ == RHS.variables_;
  }

  inline const StringSet& get_variables() const {
    return variables_;
  }

  inline void add_variables(StringSet variables) {
    variables_.merge(variables);
  }

 private:
  StringSet variables_;
};
}  // namespace pkb

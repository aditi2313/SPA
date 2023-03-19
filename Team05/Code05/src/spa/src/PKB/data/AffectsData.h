#pragma once

#include <unordered_set>
#include <cassert>

#include "Data.h"

namespace pkb {
class AffectsData : public Data<int> {
 public:
  explicit AffectsData(
      int line, std::unordered_set<int> affected_lines);

  friend bool operator==(const AffectsData &LHS, const AffectsData &RHS) {
    return LHS.line_ == RHS.line_
        && LHS.affected_lines_ == RHS.affected_lines_;
  }

  inline std::unordered_set<int> &get_affected_lines() {
    return affected_lines_;
  }

 private:
  std::unordered_set<int> affected_lines_;
};

typedef AffectsData AffectsTData;
}  // namespace pkb

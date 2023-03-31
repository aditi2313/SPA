#pragma once

#include <unordered_set>
#include <cassert>

#include "Data.h"
#include "Types.h"

namespace pkb {
class AffectsData : public Data<Line> {
 public:
  explicit AffectsData(
          Line line, LineSet affected_lines);

  friend bool operator==(const AffectsData &LHS, const AffectsData &RHS) {
    return LHS.line_ == RHS.line_ &&
           LHS.affected_lines_ == RHS.affected_lines_;
  }

  inline LineSet &get_affected_lines() {
    return affected_lines_;
  }

 private:
    LineSet affected_lines_;
};

typedef AffectsData AffectsTData;
}  // namespace pkb

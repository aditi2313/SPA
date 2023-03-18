#pragma once

#include <unordered_set>
#include <cassert>

namespace pkb {
class AffectsData {
 public:
  explicit AffectsData(
      int line, std::unordered_set<int> affected_lines);

  friend bool operator==(const AffectsData& LHS, const AffectsData& RHS) {
    return LHS.line_ == RHS.line_ &&
        LHS.affected_lines_ == RHS.affected_lines_;
  }

  inline int get_index() { return line_; }

  inline std::unordered_set<int>& get_affected_lines() { return affected_lines_; }

 private:
  int line_;
  std::unordered_set<int> affected_lines_;
};
}  // namespace pkb

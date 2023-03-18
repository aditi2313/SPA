#pragma once

#include <unordered_set>
#include <cassert>

namespace pkb {
class AffectsData {
 public:
  explicit AffectsData(
      int line, std::unordered_set<int> affected_lines);

  friend bool operator==(const AffectsData &LHS, const AffectsData &RHS) {
    return LHS.line_ == RHS.line_
        && LHS.affected_lines_ == RHS.affected_lines_
        && LHS.affectedT_lines_ == RHS.affectedT_lines_;
  }

  inline int get_index() { return line_; }

  inline bool is_affectsT_calculated() {
    return is_affectsT_calculated_;
  }

  inline std::unordered_set<int> &get_affected_lines() {
    return affected_lines_;
  }

  inline std::unordered_set<int> &get_affectedT_lines() {
    return affectedT_lines_;
  }

  inline void set_affectedT_lines(std::unordered_set<int> &affectedT_lines) {
    is_affectsT_calculated_ = true;
    affectedT_lines_ = affectedT_lines;
  }

 private:
  int line_;
  // Note: we need a separate flag for this because
  // affectedT_lines.empty() != it hasn't been calculated before
  bool is_affectsT_calculated_ = false;

  std::unordered_set<int> affected_lines_;
  // Named it affectedT_lines instead of all_affected_lines
  // because affects_t is not really semantically equivalent
  // to all_affected_lines
  std::unordered_set<int> affectedT_lines_;
};
}  // namespace pkb

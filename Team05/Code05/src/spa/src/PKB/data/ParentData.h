#pragma once

#include <unordered_set>

namespace pkb {
class ParentData {
 public:
  ParentData(int parent, int child);
  friend bool operator==(const ParentData& LHS, const ParentData& RHS) {
      return LHS.line_ == RHS.line_ && LHS.child_line_ == RHS.child_line_ &&
      LHS.children_ == RHS.children_;
  }

  inline int get_line() { return line_; }

  inline int get_child() { return child_line_; }

  inline std::unordered_set<int>& get_children_set() { return children_; }

  inline void add_children(int child) { children_.insert(child); }

 private:
  int line_;
  // the immediate parent
  int child_line_;

  // set of all parents
  std::unordered_set<int> children_;
};
}  // namespace pkb

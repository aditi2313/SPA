#pragma once

#include <unordered_set>

namespace pkb {
class ParentData {
 public:
  ParentData(int parent, int child);

  inline int get_line() { return line_; }

  inline int get_child() { return child_line_; }

  inline std::unordered_set<int>& get_children_set() { return children_; }

  inline void add_children(int parent) { children_.insert(parent); }

 private:
  int line_;
  // the immediate parent
  int child_line_;

  // set of all parents
  std::unordered_set<int> children_;
};
}  // namespace pkb

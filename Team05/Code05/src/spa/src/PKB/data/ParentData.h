#pragma once

#include <unordered_set>

namespace pkb {
class ParentData {
 public:
  ParentData(int parent);

  inline int get_line() { return line_; }

  inline std::unordered_set<int> get_direct_children() {
    return direct_children_;
  }

  inline std::unordered_set<int>& get_children_set() { return children_; }

  inline void add_children(int child) { children_.insert(child); }

  inline void add_direct_child(int child) { children_.insert(child); }

 private:
  int line_;
  // the immediate children
  std::unordered_set<int> direct_children_;

  // the set of all children
  std::unordered_set<int> children_;
};
}  // namespace pkb

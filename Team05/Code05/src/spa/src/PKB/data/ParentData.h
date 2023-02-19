#pragma once

#include <unordered_set>

namespace pkb {
class ParentData {
 public:
  explicit ParentData(int parent);

  inline int get_line() { return line_; }

  inline std::unordered_set<int> get_direct_children() {
    return direct_children_;
  }

  // all the children
  inline std::unordered_set<int>& get_all_children() { return total_children_; }

  inline void add_children(int child) { total_children_.insert(child); }

  inline void add_direct_child(int child) { direct_children_.insert(child); }

 private:
  int line_;
  // the immediate children
  std::unordered_set<int> direct_children_;

  // the set of all children
  std::unordered_set<int> total_children_;
};
}  // namespace pkb

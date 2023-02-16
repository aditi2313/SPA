#pragma once

#include <unordered_set>

namespace pkb {
class ParentData {
 public:
  ParentData(int line, int parent_line);

  inline int get_line() { return line_; }

  inline int get_parent() { return parent_line_; }

  inline std::unordered_set<int>& get_parent_set() { return parents_; }

  inline void add_parent(int parent) { parents_.insert(parent); }

 private:
  int line_;
  // the immediate parent
  int parent_line_;

  // set of all parents
  std::unordered_set<int> parents_;
};
}  // namespace pkb

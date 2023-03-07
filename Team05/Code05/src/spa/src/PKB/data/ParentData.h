#pragma once

#include <unordered_set>

namespace pkb {
class ParentData {
 public:
  explicit ParentData(int parent);
  friend bool operator==(const ParentData& LHS, const ParentData& RHS) {
    return LHS.line_ == RHS.line_ &&
           LHS.direct_children_ == RHS.direct_children_ &&
           LHS.total_children_ == RHS.total_children_;
  }

  inline int get_index() { return line_; }

  inline std::unordered_set<int> get_direct_children() {
    return direct_children_;
  }

  // all the children
  inline std::unordered_set<int>& get_all_children() { return total_children_; }

  inline void add_direct_child(int child) {
    direct_children_.insert(child);
    total_children_.insert(child);
  }

  inline void AddData(ParentData& data) {
    auto other_data = data.total_children_;
    total_children_.merge(other_data);
  }

 private:
  int line_;
  // the immediate children
  std::unordered_set<int> direct_children_;

  // the set of all children
  std::unordered_set<int> total_children_;
};
}  // namespace pkb

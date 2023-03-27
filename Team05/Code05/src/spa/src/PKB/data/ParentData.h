#pragma once

#include <unordered_set>

#include "Data.h"

namespace pkb {
class ParentData : public Data<int, int> {
 public:
  explicit ParentData(int parent);
  friend bool operator==(const ParentData& LHS, const ParentData& RHS) {
    return LHS.line_ == RHS.line_ &&
           LHS.second_indexes_ == RHS.second_indexes_ &&
           LHS.total_children_ == RHS.total_children_;
  }

  inline std::unordered_set<int> get_direct_children() {
    return second_indexes_;
  }

  // all the children
  inline std::unordered_set<int>& get_all_children() {
      return total_children_;
  }

  inline void add_direct_child(int child) {
    second_indexes_.insert(child);
    total_children_.insert(child);
  }

  inline void AddData(ParentData& data) {
    auto other_data = data.total_children_;
    total_children_.merge(other_data);
  }

 private:
  // the set of all children
  std::unordered_set<int> total_children_;
};
}  // namespace pkb

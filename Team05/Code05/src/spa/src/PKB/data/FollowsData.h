#pragma once

#include <unordered_set>

#include "Data.h"

namespace pkb {
class FollowsData : public Data<int, int> {
 public:
  FollowsData(int line, int follows);

  friend bool operator==(const FollowsData& LHS, const FollowsData& RHS) {
    return LHS.line_ == RHS.line_ &&
        LHS.follows_ == RHS.follows_ &&
        LHS.second_indexes_ == RHS.second_indexes_;
  }

  inline int get_follows() { return follows_; }

  inline std::unordered_set<int>& get_follows_list() { return second_indexes_; }

  inline void AddData(FollowsData& data) {
    for (int v : data.second_indexes_) {
        second_indexes_.insert(v);
    }
  }

 private:
  int follows_;
};
}  // namespace pkb

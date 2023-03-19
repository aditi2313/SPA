#pragma once

#include <unordered_set>

#include "Data.h"

namespace pkb {
class FollowsData : public Data<int> {
 public:
  FollowsData(int line, int follows);

  friend bool operator==(const FollowsData& LHS, const FollowsData& RHS) {
    return LHS.line_ == RHS.line_ && LHS.follows_ == RHS.follows_ &&
           LHS.follows_list_ == RHS.follows_list_;
  }

  inline int get_follows() { return follows_; }

  inline std::unordered_set<int>& get_follows_list() { return follows_list_; }

  inline void AddData(FollowsData& data) {
    for (int v : data.follows_list_) {
      follows_list_.insert(v);
    }
  }

 private:
  int follows_;
  std::unordered_set<int> follows_list_;
};
}  // namespace pkb

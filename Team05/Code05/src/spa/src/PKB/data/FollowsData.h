#pragma once

#include <unordered_set>

#include "Data.h"
#include "Types.h"

namespace pkb {
class FollowsData : public Data<Line, Line> {
 public:
  FollowsData(Line line, Line follows);

  friend bool operator==(const FollowsData& LHS, const FollowsData& RHS) {
    return LHS.line_ == RHS.line_ &&
           LHS.follows_ == RHS.follows_ &&
           LHS.second_indexes_ == RHS.second_indexes_;
  }

  inline int get_follows() const { return follows_; }

  inline const LineSet& get_follows_list() const {
    return second_indexes_;
  }

  inline void AddData(FollowsData& data) {
    for (Line v : data.second_indexes_) {
      second_indexes_.insert(v);
    }
  }

 private:
    Line follows_;
};
}  // namespace pkb

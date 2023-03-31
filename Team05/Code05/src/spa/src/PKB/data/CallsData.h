#pragma once

#include <string>
#include <unordered_set>

#include "Data.h"
#include "Types.h"

namespace pkb {
class CallsData : public Data<Proc, Proc> {
 public:
  explicit CallsData(Proc caller);

  friend bool operator==(const CallsData& LHS, const CallsData& RHS) {
    return LHS.line_ == RHS.line_ &&
           LHS.second_indexes_ == RHS.second_indexes_ &&
           LHS.total_calls_ == RHS.total_calls_;
  }

  inline const ProcSet& get_direct_calls() const {
    return second_indexes_;
  }

  inline const ProcSet& get_total_calls() const {
    return total_calls_;
  }

  inline void add_to_direct_calls(Proc c) {
      second_indexes_.insert(c);
  }

  inline void add_to_total_calls(Proc c) {
      total_calls_.insert(c);
  }

 private:
  // set of all calls
  ProcSet total_calls_;
};
}  // namespace pkb

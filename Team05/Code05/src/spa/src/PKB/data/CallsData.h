#pragma once

#include <string>
#include <unordered_set>

#include "Data.h"

namespace pkb {
class CallsData : public Data<std::string, std::string> {
 public:
    explicit CallsData(std::string caller);

    friend bool operator==(const CallsData& LHS, const CallsData& RHS) {
        return LHS.line_ == RHS.line_
        && LHS.second_indexes_ == RHS.second_indexes_
        && LHS.total_calls_ == RHS.total_calls_;
    }

    inline const std::unordered_set<std::string>& get_direct_calls() 
      const {
      return second_indexes_;
    }

    inline const std::unordered_set<std::string>& get_total_calls() 
      const {
        return total_calls_;
    }

    inline void add_to_direct_calls(std::string c) {
        second_indexes_.insert(c);
    }

    inline void add_to_total_calls(std::string c) {
        total_calls_.insert(c);
    }

 private:
    // set of all calls
    std::unordered_set<std::string> total_calls_;
};
}  // namespace pkb

#pragma once

#include <string>
#include <unordered_set>

namespace pkb {
class CallsData {
 public:
    explicit CallsData(std::string caller);

    friend bool operator==(const CallsData& LHS, const CallsData& RHS) {
        return LHS.caller_ == RHS.caller_
        && LHS.direct_calls_ == RHS.direct_calls_
        && LHS.total_calls_ == RHS.total_calls_;
    }

    inline std::string get_line() { return caller_; }

    inline std::unordered_set<std::string>& get_direct_calls() {
        return direct_calls_;
    }

    inline std::unordered_set<std::string>& get_total_calls() {
        return total_calls_;
    }

    inline void add_to_direct_calls(std::string c) {
        direct_calls_.insert(c);
    }

    inline void add_to_total_calls(std::string c) {
        total_calls_.insert(c);
    }

 private:
    std::string caller_;

    // set of direct calls
    std::unordered_set<std::string> direct_calls_;

    // set of all calls
    std::unordered_set<std::string> total_calls_;
};
}  // namespace pkb

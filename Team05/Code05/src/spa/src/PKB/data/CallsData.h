#pragma once

#include <string>
#include <unordered_set>

namespace pkb {
class CallsData {
 public:
    CallsData(std::string caller, std::string callee);

    friend bool operator==(const CallsData& LHS, const CallsData& RHS) {
        return LHS.caller_ == RHS.caller_
        && LHS.callee_ == RHS.callee_
        && LHS.callee_list_ == RHS.callee_list_;
    }

    inline std::string get_line() { return caller_; }

    inline std::string get_callee() { return callee_; }

    inline std::unordered_set<std::string>& get_callee_list() {
        return callee_list_;
    }

    inline void add_to_list(std::string c) { callee_list_.insert(c); }

 private:
    std::string caller_;
    std::string callee_;
    std::unordered_set<std::string> callee_list_;
};
}  // namespace pkb

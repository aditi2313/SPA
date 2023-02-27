#pragma once

#include <unordered_set>

namespace pkb {
class NextData {
 public:
    NextData(int line, int next);

    friend bool operator==(const NextData& LHS, const NextData& RHS) {
        return LHS.line_ == RHS.line_ && LHS.next_ == RHS.next_ &&
        LHS.next_list_ == RHS.next_list_;
    }

    inline int get_line() { return line_; }

    inline int get_next() { return next_; }

    inline std::unordered_set<int>& get_next_list() { return next_list_; }

    inline void add_to_list(int v) { next_list_.insert(v); }

 private:
    int line_;
    int next_;
    std::unordered_set<int> next_list_;
};
}  // namespace pkb

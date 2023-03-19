#pragma once

#include <unordered_set>
#include <cassert>

#include "Data.h"

namespace pkb {
class NextData : public Data<int> {
 public:
    explicit NextData(int line);

    friend bool operator==(const NextData& LHS, const NextData& RHS) {
        return LHS.line_ == RHS.line_ &&
        LHS.next_im_list_ == RHS.next_im_list_;
    }

    inline std::unordered_set<int>& get_next_im_list() { return next_im_list_; }

    inline void add_to_next_im_list(int v) {
        assert(next_im_list_.size() < 2);
        next_im_list_.insert(v);
    }

 private:
    std::unordered_set<int> next_im_list_;
};
}  // namespace pkb

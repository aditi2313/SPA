#pragma once

#include <unordered_set>
#include <cassert>

#include "Data.h"
#include "Types.h"

namespace pkb {
class NextData : public Data<int, int> {
 public:
    explicit NextData(int line);

    friend bool operator==(const NextData& LHS, const NextData& RHS) {
        return LHS.line_ == RHS.line_ &&
        LHS.second_indexes_ == RHS.second_indexes_;
    }

    inline const LineSet& get_next_im_list() const {
        return second_indexes_;
    }

    inline void add_to_next_im_list(int v) {
        assert(second_indexes_.size() < 2);
        second_indexes_.insert(v);
    }
};
}  // namespace pkb

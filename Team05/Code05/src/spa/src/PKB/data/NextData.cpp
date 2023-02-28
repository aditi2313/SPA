#include "NextData.h"

namespace pkb {
pkb::NextData::NextData(int line, int next)
    : line_(line), next_(next) {
    next_im_list_.insert(next);
}
}  // namespace pkb

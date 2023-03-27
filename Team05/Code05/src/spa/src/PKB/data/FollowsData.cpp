#include "FollowsData.h"

namespace pkb {
pkb::FollowsData::FollowsData(int line, int follows)
    : Data<int, int>(line), follows_(follows) {
    second_indexes_.insert(follows);
}
}  // namespace pkb

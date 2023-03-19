#include "FollowsData.h"

namespace pkb {
pkb::FollowsData::FollowsData(int line, int follows)
    : Data<int>(line), follows_(follows) {
  follows_list_.insert(follows);
}
}  // namespace pkb

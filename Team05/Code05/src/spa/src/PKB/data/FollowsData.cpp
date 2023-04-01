#include "FollowsData.h"

namespace pkb {
pkb::FollowsData::FollowsData(Line line, Line follows)
    : Data<Line, Line>(line), follows_(follows) {
    second_indexes_.insert(follows);
}
}  // namespace pkb

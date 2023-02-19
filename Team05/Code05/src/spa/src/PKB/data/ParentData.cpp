#include "ParentData.h"

namespace pkb {
pkb::ParentData::ParentData(int parent, int child)
    : line_(parent), child_line_(child) {}
}  // namespace pkb

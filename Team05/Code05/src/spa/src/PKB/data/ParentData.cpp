#include "ParentData.h"

namespace pkb {
pkb::ParentData::ParentData(int line, int parent_line)
    : line_(line), parent_line_(parent_line) {
  parents_list.insert(parent_line);
}
}  // namespace pkb

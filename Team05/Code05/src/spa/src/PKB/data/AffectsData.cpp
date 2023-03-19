#include "AffectsData.h"

namespace pkb {
pkb::AffectsData::AffectsData(int line, std::unordered_set<int> affected_lines)
    : Data<int>(line), affected_lines_(affected_lines) {}
}  // namespace pkb

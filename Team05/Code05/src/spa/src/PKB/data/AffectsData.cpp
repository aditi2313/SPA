#include "AffectsData.h"

namespace pkb {
pkb::AffectsData::AffectsData(int line, LineSet affected_lines)
    : Data<int>(line), affected_lines_(affected_lines) {}
}  // namespace pkb

#include "AffectsData.h"

namespace pkb {
pkb::AffectsData::AffectsData(Line line, LineSet affected_lines)
    : Data<Line>(line), affected_lines_(affected_lines) {}
}  // namespace pkb

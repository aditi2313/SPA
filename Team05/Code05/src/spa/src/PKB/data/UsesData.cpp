#include "UsesData.h"
#include <unordered_set>

namespace pkb {
pkb::UsesData::UsesData(Index line,
                        const StringSet& variable_names)
    : Data<Index>(line),
    variable_names_(variable_names) {}
}  // namespace pkb

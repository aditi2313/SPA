#include "UsesData.h"
#include <unordered_set>

namespace pkb {
pkb::UsesData::UsesData(int line,
                        const std::unordered_set<std::string>& variable_names)
    : line_(line), variable_names_(variable_names) {}
}  // namespace pkb

#include "UsesData.h"

namespace pkb {
pkb::UsesData::UsesData(int line,
                        const std::vector<std::string>& variable_names)
    : line_(line), variable_names_(variable_names) {}
}  // namespace pkb
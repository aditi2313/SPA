#include "ConditionData.h"

namespace pkb {
pkb::ConditionData::ConditionData(std::variant<int, std::string> line,
                        const std::unordered_set<std::string>& variable_names)
    : line_(line), variable_names_(variable_names) {}
}  // namespace pkb

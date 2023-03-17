#include "ConditionData.h"

namespace pkb {
pkb::ConditionData::ConditionData(std::variant<int, std::string> line,
                        const std::unordered_set<std::string>& control_variable_names)
    : line_(line), control_variable_names_(control_variable_names) {}
}  // namespace pkb
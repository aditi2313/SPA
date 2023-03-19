#include "ConditionData.h"

namespace pkb {
pkb::ConditionData::ConditionData(std::variant<int, std::string> line,
                        const std::unordered_set<std::string>& variable_names)
    : Data<std::variant<int, std::string>>(line),
    variable_names_(variable_names) {}
}  // namespace pkb

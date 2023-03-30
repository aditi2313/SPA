#include "ConditionData.h"

namespace pkb {
pkb::ConditionData::ConditionData(Index line,
                        const StringSet& variable_names)
    : Data<Index>(line),
    variable_names_(variable_names) {}
}  // namespace pkb

#include "ConditionData.h"

namespace pkb {
pkb::ConditionData::ConditionData(Key line,
                        const VarSet& variable_names)
    : Data<Key>(line),
    variable_names_(variable_names) {}
}  // namespace pkb

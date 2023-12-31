#include "UsesData.h"
#include <unordered_set>

namespace pkb {
pkb::UsesData::UsesData(Key line,
                        const VarSet& variable_names)
    : Data<Key>(line),
    variable_names_(variable_names) {}
}  // namespace pkb

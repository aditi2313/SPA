#include "ModifiesData.h"
#include <unordered_set>

namespace pkb {
ModifiesData::ModifiesData(Key line,
                           const VarSet& variables)
    : Data<Key>(line), variables_(variables) {}
}  // namespace pkb

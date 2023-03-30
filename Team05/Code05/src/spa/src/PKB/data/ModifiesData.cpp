#include "ModifiesData.h"
#include <unordered_set>

namespace pkb {
ModifiesData::ModifiesData(Key line,
                           const StringSet& variables)
    : Data<Key>(line), variables_(variables) {}
}  // namespace pkb

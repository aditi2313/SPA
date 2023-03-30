#include "ModifiesData.h"
#include <unordered_set>

namespace pkb {
ModifiesData::ModifiesData(Index line,
                           const StringSet& variables)
    : Data<Index>(line), variables_(variables) {}
}  // namespace pkb

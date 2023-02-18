#include "ModifiesData.h"
#include <unordered_set>

namespace pkb {
ModifiesData::ModifiesData(int line,
                           const std::unordered_set<std::string>& variables)
    : line_(line), variables_(variables) {}
}  // namespace pkb

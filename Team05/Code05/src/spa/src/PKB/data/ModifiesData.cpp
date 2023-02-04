#include "ModifiesData.h"

namespace pkb {
ModifiesData::ModifiesData(int line, const std::vector<std::string>& variables)
    : line_(line), variables_(variables) {}
}  // namespace pkb

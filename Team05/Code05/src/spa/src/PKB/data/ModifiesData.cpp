#include "ModifiesData.h"
#include <unordered_set>

namespace pkb {
ModifiesData::ModifiesData(std::variant<int, std::string> line,
                           const std::unordered_set<std::string>& variables)
    : Data<std::variant<int, std::string>>(line), variables_(variables) {}
}  // namespace pkb

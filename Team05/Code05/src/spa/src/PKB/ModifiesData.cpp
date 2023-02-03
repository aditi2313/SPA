#include "ModifiesData.h"

namespace pkb {
    ModifiesData::ModifiesData(int line, std::vector<std::string> variables) {
        line_ = line;
        variables_ = variables;
    }
}  // namespace pkb

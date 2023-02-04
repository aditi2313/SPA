#include "PKBWrite.h"

#include <string>
#include <vector>

#include "common/Exceptions.h"

namespace pkb {

void PKBWrite::AddModifiesDataData(const int line,
                           const std::vector<std::string>& variables) {
  pkb_relation_table->add_modifies_data(line, variables);
}

}  // namespace pkb

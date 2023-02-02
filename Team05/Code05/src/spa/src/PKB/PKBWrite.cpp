#include "PKBWrite.h"

#include "common/Exceptions.h"

namespace pkb {

void PKBWrite::AddModifies(const int line, const std::vector<std::string>& variables) {
  pkb_relation_table->add_modifies(line, variables);
}

void PKBWrite::AddParent(stub::ParentStub) {
  throw new NotImplementedException();
}

}  // namespace pkb

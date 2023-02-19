#include "ProcedureValidator.h"

#include <unordered_set>
#include <utility>
#include "common/exceptions/SPExceptions.h"

namespace sp {
void ProcedureValidator::Validate() {
  return ValidateNoDuplicateProcedureNames();
}

void ProcedureValidator::ValidateNoDuplicateProcedureNames() {
  std::unordered_set<std::string> proc_names_set;
  for (const auto &proc_name : proc_names_) {
    if (proc_names_set.count(proc_name)) {
      throw ProcedureSemanticsException("duplicate procedure name: "
                                        + proc_name);
    }
    proc_names_set.insert(proc_name);
  }
}

void ProcedureValidator::Accept(ast::ProcNode &proc_node) {
  proc_names_.push_back(proc_node.get_name());
}
}  // namespace sp

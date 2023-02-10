#include "ProcedureValidator.h"
#include <unordered_set>
#include <utility>

namespace sp {
bool ProcedureValidator::Validate() {
  return ValidateNoDuplicateProcedureNames();
}

bool ProcedureValidator::ValidateNoDuplicateProcedureNames() {
  std::unordered_set<std::string> proc_names_set;
  for (const auto &proc_name : proc_names_) {
    if (proc_names_set.count(proc_name)) {
      return false;
    }
    proc_names_set.insert(proc_name);
  }
  return true;
}

void ProcedureValidator::Accept(ast::ProcNode &proc_node) {
  proc_names_.push_back(proc_node.get_name());
}
}  // namespace sp

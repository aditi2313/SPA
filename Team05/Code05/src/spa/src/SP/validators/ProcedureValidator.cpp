#include "ProcedureValidator.h"
#include <unordered_set>
#include <utility>

namespace sp {
ProcedureValidator::ProcedureValidator(std::vector<std::string> proc_names)
    : proc_names_(std::move(proc_names)) {}

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
}  // namespace sp

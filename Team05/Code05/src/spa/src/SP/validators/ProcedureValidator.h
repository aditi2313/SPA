#pragma once

#include <string>
#include <vector>

#include "Validator.h"
#include "../../models/AST/ProcNode.h"

namespace sp {
class ProcedureValidator : public Validator {
 public:
  void Validate() override;

  void Accept(ast::ProcNode &proc_node);

 private:
  std::vector<std::string> proc_names_;

  void ValidateNoDuplicateProcedureNames();
};
}  // namespace sp

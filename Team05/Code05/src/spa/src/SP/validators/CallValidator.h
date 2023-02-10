#pragma once

#include <string>
#include <utility>
#include <vector>
#include <unordered_set>

#include "Validator.h"
#include "models/AST/ProcNode.h"

namespace sp {

class CallValidator : public Validator {
 public:
  bool Validate() override;

  void Accept(ast::ProcNode &proc_node);
  void Accept(ast::CallNode &call_node);

 private:
  std::unordered_set<std::string> procedure_names_set_;
  std::unordered_set<std::string> call_names_set;

  bool ValidateProcedureNameExists();
};

}  // namespace sp

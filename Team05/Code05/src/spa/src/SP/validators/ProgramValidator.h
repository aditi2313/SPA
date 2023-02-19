#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "CallValidator.h"
#include "ProcedureValidator.h"
#include "SP/visitors/ValidatorVisitor.h"
#include "Validator.h"
#include "models/AST/ProgramNode.h"

namespace sp {
class ProgramValidator : public Validator, ValidatorVisitor {
 public:
  explicit ProgramValidator(std::unique_ptr<ast::ProgramNode>& root)
      : root_(root) {}

  void Validate() override;

  void Process(ast::ProcNode* proc_node) override;
  void Process(ast::CallNode* call_node) override;

 private:
  std::unique_ptr<ast::ProgramNode>& root_;
  sp::ProcedureValidator procedure_validator_;
  sp::CallValidator call_validator_;
};
}  // namespace sp

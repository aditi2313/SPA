#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "PKBWritingVisitor.h"
#include "SP/visitors/TNodeVisitor.h"

namespace sp {
class DataVisitor : public PKBWritingVisitor {
 public:
  explicit DataVisitor(std::unique_ptr<pkb::PKBWrite>&& pkb_ptr)
      : PKBWritingVisitor(std::move(pkb_ptr)) {}

  void PerformWork(ast::ProcNode* proc_node) override;

  void PerformWork(ast::AssignNode* assign_node) override;
  void VisitRead(ast::ReadNode* read_node) override;

  void VisitPrint(ast::PrintNode* print_node) override;

  void VisitVar(ast::VarNode* var_node) override;

  void VisitConst(ast::ConstNode* const_node) override;

  void VisitCall(ast::CallNode* call_node) override;

  void VisitWhile(ast::WhileNode* assign_node) override;

  void VisitIf(ast::IfNode* if_node) override;
};
}  // namespace sp

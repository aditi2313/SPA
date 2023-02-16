#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "PKB/PKBWrite.h"
#include "models/AST/ProgramNode.h"
#include "models/AST/relations/CondExprNode.h"
#include "models/AST/relations/RelExprNode.h"

namespace sp {
class TNodeVisitor {
 public:
  virtual void VisitProgram(ast::ProgramNode* program_node) {}

  virtual void VisitProc(ast::ProcNode* proc_node) {}

  virtual void VisitStmtLst(ast::StmtLstNode* stmtlst_node) {}

  virtual void VisitAssign(ast::AssignNode* assign_node) {}

  virtual void VisitRead(ast::ReadNode* read_node) {}

  virtual void VisitPrint(ast::PrintNode* print_node) {}

  virtual void VisitIf(ast::IfNode*);

  virtual void VisitWhile(ast::WhileNode*);

  virtual void VisitCall(ast::CallNode* call_node) {}

  virtual void VisitExpr(ast::ExprNode* expr_node) {}

  virtual void VisitVar(ast::VarNode* var_node) {}

  virtual void VisitConst(ast::ConstNode* const_node) {}

  // Relational nodes

  virtual void VisitNot(ast::NotExprNode*) {}

  virtual void VisitDoubleCond(ast::DoubleCondExprNode*) {}

  virtual void VisitRelExpr(ast::RelExprNode*) {}

  virtual void VisitRelFactor(ast::RelFactor*) {}
};
}  // namespace sp

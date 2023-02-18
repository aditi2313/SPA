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
/*
 Implements a template for visiting of all children for every type of TNode
 since it is common for all subclasses.

 If required, subclasses can override the respective PerformWork(TNode) method
 which will be called before visiting the children.
 */
class TNodeVisitor {
 public:
  void VisitProgram(ast::ProgramNode* program_node);
  virtual void PerformWork(ast::ProgramNode* program_node) {};

  void VisitProc(ast::ProcNode* proc_node);
  virtual void PerformWork(ast::ProcNode* proc_node) {};

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

  virtual void VisitOpNode(ast::OpNode* op_node);

  // Relational nodes

  virtual void VisitNot(ast::NotExprNode*) {}

  virtual void VisitDoubleCond(ast::DoubleCondExprNode*) {}

  virtual void VisitRelExpr(ast::RelExprNode*) {}

  virtual void VisitRelFactor(ast::RelFactor*) {}
};
}  // namespace sp

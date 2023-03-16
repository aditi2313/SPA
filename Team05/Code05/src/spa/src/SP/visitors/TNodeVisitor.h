#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "PKB/PKBWrite.h"
#include "models/AST/ProgramNode.h"
#include "models/AST/relations/CondExprNode.h"
#include "models/AST/relations/RelExprNode.h"
#include "models/AST/stmt_node/Export.h"

namespace sp {
/*
 Implements a template for visiting of all children for every type of TNode
 since it is common for all subclasses.

 If required, subclasses can override the respective Process(TNode) method.
 */
class TNodeVisitor {
 public:
  void VisitProgram(ast::ProgramNode* program_node);
  virtual void Process(ast::ProgramNode* program_node) {}
  virtual void ProcessAfter(ast::ProgramNode* program_node) {}

  void VisitProc(ast::ProcNode* proc_node);
  virtual void Process(ast::ProcNode* proc_node) {}

  void VisitStmtLst(ast::StmtLstNode* stmtlst_node);
  virtual void Process(ast::StmtLstNode* stmtlst_node) {}
  virtual void ProcessAft(ast::StmtLstNode* stmtlst_node) {}

  void VisitAssign(ast::AssignNode* assign_node);
  virtual void Process(ast::AssignNode* assign_node) {}

  void VisitRead(ast::ReadNode* read_node);
  virtual void Process(ast::ReadNode* read_node) {}

  void VisitPrint(ast::PrintNode* print_node);
  virtual void Process(ast::PrintNode* print_node) {}

  void VisitIf(ast::IfNode*);
  virtual void Process(ast::IfNode* if_node) {}
  virtual void ProcessAft(ast::IfNode* if_node) {}

  void VisitWhile(ast::WhileNode*);
  virtual void Process(ast::WhileNode* while_node) {}
  virtual void ProcessAft(ast::WhileNode* if_node) {}

  void VisitCall(ast::CallNode* call_node);
  virtual void Process(ast::CallNode* call_node) {}

  void VisitExpr(ast::ExprNode* expr_node);
  virtual void Process(ast::ExprNode* expr_node) {}

  void VisitVar(ast::VarNode* var_node);
  virtual void Process(ast::VarNode* var_node) {}

  void VisitConst(ast::ConstNode* const_node);
  virtual void Process(ast::ConstNode* const_node) {}

  void VisitOpNode(ast::OpNode* op_node);
  virtual void Process(ast::OpNode* op_node) {}

  // Relational nodes

  void VisitNot(ast::NotExprNode*);
  virtual void Process(ast::NotExprNode*) {}

  void VisitDoubleCond(ast::DoubleCondExprNode*);
  virtual void Process(ast::DoubleCondExprNode*) {}

  void VisitRelExpr(ast::RelExprNode*);
  virtual void Process(ast::RelExprNode*) {}

  void VisitRelFactor(ast::RelFactor*);
  virtual void Process(ast::RelFactor*) {}
};
}  // namespace sp

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

  virtual void VisitOpNode(ast::OpNode* op_node) {
    op_node->get_left()->AcceptVisitor(this);
    op_node->get_right()->AcceptVisitor(this);
  }

  // Relational nodes

  virtual void VisitNot(ast::NotExprNode* not_node) {
    not_node->get_cond()->AcceptVisitor(this);
  }

  virtual void VisitDoubleCond(ast::DoubleCondExprNode* double_node) {
    double_node->get_left_cond()->AcceptVisitor(this);
    double_node->get_right_cond()->AcceptVisitor(this);
  }

  virtual void VisitRelExpr(ast::RelExprNode* rel_node) {
    rel_node->get_left_factor()->AcceptVisitor(this);
    rel_node->get_right_factor()->AcceptVisitor(this);
  }

  virtual void VisitRelFactor(ast::RelFactor* rel_factor) {
    rel_factor->get_expr()->AcceptVisitor(this);
  }
};
}  // namespace sp

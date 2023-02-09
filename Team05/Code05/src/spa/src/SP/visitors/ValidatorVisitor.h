#pragma once

#include "models/AST/ProgramNode.h"

namespace sp {

class ValidatorVisitor {
 public:
  virtual void Visit(ast::ProgramNode *program_node) = 0;
  virtual void Visit(ast::StmtLstNode *stmtlst_node) = 0;
  virtual void Visit(ast::ProcNode *proc_node) = 0;
  virtual void Visit(ast::ReadNode *read_node) = 0;
  virtual void Visit(ast::PrintNode *print_node) = 0;
  virtual void Visit(ast::CallNode *call_node) = 0;
  virtual void Visit(ast::AssignNode *assign_node) = 0;
  virtual void Visit(ast::FactorNode *factor_node) = 0;
  virtual void Visit(ast::ExprNode *expr_node) = 0;
  virtual void Visit(ast::TermNode *term_node) = 0;
  virtual void Visit(ast::VarNode *var_node) = 0;
  virtual void Visit(ast::ConstNode *const_node) = 0;
  virtual void Visit(ast::PlusNode *plus_node) = 0;
  virtual void Visit(ast::MinusNode *minus_node) = 0;
  virtual void Visit(ast::TimesNode *times_node) = 0;
  virtual void Visit(ast::DivNode *div_node) = 0;
  virtual void Visit(ast::ModNode *mod_node) = 0;
};

}  // namespace sp

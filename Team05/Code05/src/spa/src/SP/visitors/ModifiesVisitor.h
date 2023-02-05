#pragma once

#include "SP/visitors/TNodeVisitor.h"

namespace sp {
class ModifiesVisitor : public TNodeVisitor {
 public:
  virtual void VisitProgram(ast::ProgramNode* program_node) {
	
  }

  virtual void VisitProc(ast::ProcNode* proc_node) {}

  virtual void VisitAssign(ast::AssignNode* assign_node) {}
}
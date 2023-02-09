#pragma once

#include "models/AST/ProgramNode.h"

namespace sp {

class ValidatorVisitor {
 public:
    virtual void Visit(ast::ProgramNode* program_node) = 0;
    virtual void Visit(ast::ProcNode* proc_node) = 0;
    virtual void Visit(ast::ReadNode* proc_node) = 0;
    virtual void Visit(ast::PrintNode* proc_node) = 0;
    virtual void Visit(ast::CallNode* proc_node) = 0;
    virtual void Visit(ast::AssignNode* proc_node) = 0;
};

}  // namespace sp

#include "CFGGeneratingVisitor.h"

namespace sp {

void CFGGeneratingVisitor::Process(ast::ProcNode* proc_node) {
  auto& cfg = program_cfg_.add_procedure(proc_node->get_name());
  current_cfg_ = &cfg;
  current_node_ = &(current_cfg_->get_root());
}

void CFGGeneratingVisitor::Process(ast::IfNode* if_node) {
  ProcStmtNode(if_node);
  cfg::CFGNode& child = AddChild();  
  current_node_ = &child;


}

void CFGGeneratingVisitor::Process(ast::CallNode* stmt_node) {
  ProcStmtNode(stmt_node);
}

void CFGGeneratingVisitor::Process(ast::ReadNode* stmt_node) {
  ProcStmtNode(stmt_node);
}

void CFGGeneratingVisitor::Process(ast::AssignNode* stmt_node) {
  ProcStmtNode(stmt_node);
}

void CFGGeneratingVisitor::Process(ast::PrintNode* stmt_node) {
  ProcStmtNode(stmt_node);
}

}  // namespace sp
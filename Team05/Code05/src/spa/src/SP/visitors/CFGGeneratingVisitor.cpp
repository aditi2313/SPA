#include "CFGGeneratingVisitor.h"

namespace sp {

void CFGGeneratingVisitor::Process(ast::ProcNode* proc_node) {
  auto& cfg = program_cfg_.add_procedure(proc_node->get_name());
  current_cfg_ = &cfg;
  parents_.push(&current_cfg_->get_root());
  cfg::CFGNode& empt = current_cfg_->AddNode();
  ends_.push(&empt);
}

void CFGGeneratingVisitor::ProcessAft(ast::StmtLstNode* stmt_lst_node) {
  AddChild();
  current_cfg_->AddChild(*parents_.top(), *ends_.top());
  ends_.pop();
  parents_.pop();
}

void CFGGeneratingVisitor::Process(ast::IfNode* if_node) {
  ProcStmtNode(if_node);
  cfg::CFGNode& child = AddChild();
  // remove the previous parent
  parents_.push(&child);
  cfg::CFGNode& empt = current_cfg_->AddNode();
  ends_.push(&empt);
  ends_.push(&empt);
}

void CFGGeneratingVisitor::Process(ast::WhileNode* while_node) {
  cfg::CFGNode& prev = AddChild();
  ProcStmtNode(while_node);
  cfg::CFGNode& child = AddChild();
  parents_.push(&child);
  ends_.push(&child);
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
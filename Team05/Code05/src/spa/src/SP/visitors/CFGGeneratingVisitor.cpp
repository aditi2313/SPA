#include "CFGGeneratingVisitor.h"

#include <cassert>

namespace sp {

void CFGGeneratingVisitor::Process(ast::ProcNode* proc_node) {
  auto& cfg = program_cfg_.add_procedure(proc_node->get_name());

  assert(parents_.empty());
  assert(ends_.empty());

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
  cfg::CFGNode& empt = current_cfg_->AddNode();

  cfg::CFGNode& child = AddChild();

  parents_.pop();
  parents_.push(&empt);
  parents_.push(&child);
  parents_.push(&child);

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

cfg::CFGNode& CFGGeneratingVisitor::AddChild() {
  auto& res =
      current_cfg_->AddChild(*parents_.top(), current_start_, current_end_);
  current_start_ = kInvalidLine;
  current_end_ = kInvalidLine;
  parents_.pop();
  parents_.push(&res);
  return res;
}

void CFGGeneratingVisitor::ProcStmtNode(ast::StmtNode* node) {
  if (current_start_ == kInvalidLine) current_start_ = node->get_line();
  current_end_ = std::max(current_end_, node->get_line());
}

}  // namespace sp

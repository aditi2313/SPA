#pragma once

#include <memory>
#include <stack>

#include "TNodeVisitor.h"
#include "models/CFG/ProgramCFG.h"

namespace sp {
class CFGGeneratingVisitor : public TNodeVisitor {
 public:
  void Process(ast::ProcNode* proc_node) override;

  void Process(ast::AssignNode* assign_node) override;

  void Process(ast::ReadNode* read_node) override;

  void Process(ast::PrintNode* print_node) override;

  void Process(ast::CallNode* call_node) override;

  void Process(ast::WhileNode* while_node) override;

  void Process(ast::IfNode* if_node) override;

  void ProcessAft(ast::StmtLstNode* stmt_node) override;

  std::unique_ptr<cfg::ProgramCFG> CreateCFG() {
    return std::make_unique<cfg::ProgramCFG>(program_cfg_);
  }

 private:
  cfg::CFGNode& AddChild() {
    auto& res =
        current_cfg_->AddChild(*parents_.top(), current_start_, current_end_);
    current_start_ = -1;
    current_end_ = -1;
    parents_.pop();
    parents_.push(&res);
    return res;
  }
  void ProcStmtNode(ast::StmtNode* node) {
    if (current_start_ == -1) current_start_ = node->get_line();
    current_end_ = std::max(current_end_, node->get_line());
  }

  cfg::ProgramCFG program_cfg_;
  cfg::CFG* current_cfg_;
  std::stack<cfg::CFGNode*> parents_;
  std::stack<cfg::CFGNode*> ends_;
  int current_start_ = -1;
  int current_end_ = -1;
};

}  // namespace sp

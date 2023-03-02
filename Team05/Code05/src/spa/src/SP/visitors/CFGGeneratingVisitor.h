#pragma once

#include <memory>

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

  std::unique_ptr<cfg::ProgramCFG> CreateCFG() {
    return std::make_unique<cfg::ProgramCFG>(program_cfg_);
  }

 private:
  cfg::CFGNode& AddChild() {
    return current_cfg_->AddChild(*current_node_, current_start_, current_end_);
  }
  void ProcStmtNode(ast::StmtNode* node) {
    if (current_start_ == -1) current_start_ = node->get_line();
    current_end_ = std::max(current_end_, node->get_line());
  }
  cfg::ProgramCFG program_cfg_;
  cfg::CFG* current_cfg_;
  cfg::CFGNode* current_node_;
  int current_start_ = -1;
  int current_end_ = -1;
};

}  // namespace sp
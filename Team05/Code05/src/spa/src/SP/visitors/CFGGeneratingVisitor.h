#pragma once

#include <algorithm>
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
  cfg::CFGNode& AddChild();
  void ProcStmtNode(ast::StmtNode* node);

  cfg::ProgramCFG program_cfg_;
  cfg::CFG* current_cfg_;
  std::stack<cfg::CFGNode*> parents_;
  std::stack<cfg::CFGNode*> ends_;
  static const int kInvalidLine = -1;
  int current_start_ = kInvalidLine;
  int current_end_ = kInvalidLine;
};

}  // namespace sp

#pragma once
#include <memory>
#include <utility>
#include <vector>

#include "models/AST/ProcNode.h"
#include "models/AST/TNode.h"

namespace ast {
class ProgramNode : public TNode {  // root node
 public:
  explicit ProgramNode(std::unique_ptr<ProcNode> proc) {
    procs_.push_back(std::move(proc));
  }
  inline void add_proc(std::unique_ptr<ProcNode> proc) {
    procs_.push_back(std::move(proc));
  }
  inline std::vector<std::unique_ptr<ProcNode>>& get_children() {
    return procs_;
  }

  inline std::unique_ptr<sp::TNodeVisitor> AcceptVisitor(
      std::unique_ptr<sp::TNodeVisitor> visitor) override {
    visitor->VisitProgram(this);
  }

 private:
  std::vector<std::unique_ptr<ProcNode>> procs_;
};
}  // namespace ast

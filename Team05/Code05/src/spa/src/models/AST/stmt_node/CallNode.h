#pragma once
#include <memory>
#include <string>
#include <utility>

#include "models/AST/TNode.h"
#include "models/AST/factor_node/FactorNode.h"
#include "models/AST/relations/CondExprNode.h"
#include "models/AST/stmt_node/StmtNode.h"

namespace ast {
class CallNode : public StmtNode {
 public:
  explicit CallNode(std::string parent_proc_name,
                    std::unique_ptr<VarNode> called_proc, int line)
      : StmtNode(line) {
    parent_proc_name_ = parent_proc_name;
    called_proc_ = std::move(called_proc);
  }

  inline std::unique_ptr<VarNode>& get_called_proc() { return called_proc_; }

  inline std::string& get_called_proc_name() {
    return called_proc_->get_name();
  }

  inline std::string& get_parent_proc() { return parent_proc_name_; }

  void AcceptVisitor(sp::TNodeVisitor* visitor) override;

 private:
  std::string parent_proc_name_;
  std::unique_ptr<VarNode> called_proc_;
};
}  // namespace ast

#pragma once
#include <memory>
#include <string>
#include <utility>

#include "models/AST/TNode.h"
#include "models/AST/factor_node/FactorNode.h"
#include "models/AST/relations/CondExprNode.h"
#include "models/AST/stmt_node/SingleVarStmtNode.h"

namespace ast {
class CallNode : public SingleVarStmtNode {
 public:
  explicit CallNode(std::string parent_proc_name, std::unique_ptr<VarNode> var,
                    int line)
      : SingleVarStmtNode(std::move(var), line) {
    parent_proc_name_ = parent_proc_name;
  }

  inline std::string& get_parent_proc() { return parent_proc_name_; }

  void AcceptVisitor(sp::TNodeVisitor* visitor) override;

 private:
  std::string parent_proc_name_;
};
}  // namespace ast

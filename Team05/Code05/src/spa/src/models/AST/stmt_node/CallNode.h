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
  explicit CallNode(std::string parent_proc_name, std::unique_ptr<VarNode> var,
                    int line)
      : StmtNode(line) {
    parent_proc_name_ = parent_proc_name;
    var_ = std::move(var);
  }

  inline std::string& get_parent_proc() { return parent_proc_name_; }
  inline std::unique_ptr<VarNode>& get_var() { return var_; }

  void AcceptVisitor(sp::TNodeVisitor* visitor) override;

 private:
  std::string parent_proc_name_;
  std::unique_ptr<VarNode> var_;
};
}  // namespace ast

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
                    std::string called_proc_name, int line)
      : StmtNode(line) {
    parent_proc_name_ = parent_proc_name;
    called_proc_name_ = called_proc_name;
  }

  inline std::string& get_called_proc() { return called_proc_name_; }

  inline std::string& get_parent_proc() { return parent_proc_name_; }

  void AcceptVisitor(sp::TNodeVisitor* visitor) override;

 private:
  std::string parent_proc_name_;
  std::string called_proc_name_;
};
}  // namespace ast

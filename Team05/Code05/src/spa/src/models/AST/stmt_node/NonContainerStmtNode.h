#pragma once

#include <memory>
#include <vector>

#include "StmtNode.h"

namespace ast {

class NonContainerStmtNode : public StmtNode {
 public:
  explicit NonContainerStmtNode(std::unique_ptr<VarNode> var, int line)
      : StmtNode(line) {
    var_ = std::move(var);
  }

  virtual inline std::unique_ptr<VarNode>& get_var() { return var_; }
  virtual inline std::string get_var_name() { return var_->get_name(); }

 protected:
  std::unique_ptr<VarNode> var_;
};
}  // namespace ast

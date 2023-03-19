#pragma once

#include <memory>
#include <vector>

#include "StmtNode.h"

namespace ast {

class ContainerNode : public StmtNode {
 public:
  explicit ContainerNode(int line) : StmtNode(line) {}
  virtual std::vector<std::unique_ptr<StmtLstNode>>& get_total_stmts() {
    return stmts_;
  }

 protected:
  std::vector<std::unique_ptr<StmtLstNode>> stmts_;
};
}  // namespace ast

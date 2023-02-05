#pragma once
#include <memory>
#include <utility>
#include <vector>

#include "models/AST/TNode.h"
#include "models/AST/stmt_node/StmtNode.h"

namespace ast {

class StmtLstNode : public TNode {
 public:
  explicit StmtLstNode(std::unique_ptr<StmtNode> stmt) {
    stmts_.push_back(std::move(stmt));
  }
  inline void add_stmt(std::unique_ptr<StmtNode> stmt) {
    stmts_.push_back(std::move(stmt));
  }

  inline std::vector<std::unique_ptr<StmtNode>>& get_children() {
    return stmts_;
  }

 private:
  std::vector<std::unique_ptr<StmtNode>> stmts_;
};
}  // namespace ast

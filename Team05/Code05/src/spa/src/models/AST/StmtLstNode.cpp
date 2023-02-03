#include "StmtLstNode.h"

namespace ast {

void StmtLstNode::add_stmt(std::unique_ptr<StmtNode> stmt) {
  stmts_.push_back(std::move(stmt));
}

}  // namespace ast

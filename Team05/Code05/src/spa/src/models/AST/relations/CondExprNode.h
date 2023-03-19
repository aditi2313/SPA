#pragma once

#include <memory>
#include <utility>

#include "models/AST/TNode.h"
#include "models/AST/factor_node/FactorNode.h"

namespace ast {

/// <summary>
/// Class reprenting a conditional expression.
/// For instance (a + b == a - b) || (a > b).
/// </summary>
class CondExprNode : public TNode {
 public:
  virtual bool DeepEquals(const CondExprNode& other) = 0;
};
}  // namespace ast

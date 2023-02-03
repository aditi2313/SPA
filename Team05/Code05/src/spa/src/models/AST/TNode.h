#pragma once

namespace ast {
class TNode {
 public:
  virtual void accept_visitor(){}
};
}  // namespace ast

#pragma once

#include <memory>

namespace sp {
class TNodeVisitor;
}

namespace ast {
class TNode {
 public:
  virtual ~TNode() = 0;

  virtual void AcceptVisitor(sp::TNodeVisitor* visitor) = 0;

 private:
};
}  // namespace ast

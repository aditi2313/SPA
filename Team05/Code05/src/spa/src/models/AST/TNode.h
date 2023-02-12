#pragma once

#include <memory>

namespace sp {
class TNodeVisitor;
}

namespace ast {
class TNode {
 public:
  virtual ~TNode() = 0;

  // TODO(nhjryan): implement accept_visitor for design extractor
  virtual void AcceptVisitor(sp::TNodeVisitor* visitor) = 0;
  virtual ~TNode() = 0;

 private:
};
}  // namespace ast

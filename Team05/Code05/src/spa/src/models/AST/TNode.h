#pragma once

#include <memory>

namespace sp {
class TNodeVisitor;
}


namespace ast {
class TNode {
 public:
  // TODO(nhjryan): implement accept_visitor for design extractor
  virtual void AcceptVisitor(sp::TNodeVisitor* visitor) = 0;

 private:
};
}  // namespace ast

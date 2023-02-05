#pragma once

#include "SP/visitors/TNodeVisitor.h"

namespace ast {
class TNode {
 public:
  // TODO(nhjryan): implement accept_visitor for design extractor
  virtual std::unique_ptr<sp::TNodeVisitor> AcceptVisitor(
      std::unique_ptr<sp::TNodeVisitor> visitor) = 0;

 private:
};
}  // namespace ast

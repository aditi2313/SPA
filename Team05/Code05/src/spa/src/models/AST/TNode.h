#pragma once

namespace ast {
class TNode {
 public:
  // TODO(nhjryan): implement accept_visitor for design extractor
  virtual void accept_visitor() {}

 private:
};
}  // namespace ast

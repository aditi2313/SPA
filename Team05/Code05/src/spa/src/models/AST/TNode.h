#pragma once

namespace ast {
class TNode {
 public:
  // TODO: implement accept_visitor for design extractor
  virtual void accept_visitor() {}
};
}  // namespace ast

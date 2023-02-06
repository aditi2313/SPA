#pragma once

#include "SP/parser/Parser.h"
#include "models/AST/factor_node/FactorNode.h"

namespace sp {
class ConstParser : Parser<ast::ConstNode> {
 public:
  std::unique_ptr<ast::ConstNode> parse(Lexer&) {}
};
}  // namespace sp
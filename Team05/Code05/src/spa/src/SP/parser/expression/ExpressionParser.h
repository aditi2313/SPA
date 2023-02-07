#pragma once

#include "SP/parser/Parser.h"

#include "models/AST/factor_node/FactorNode.h"

namespace sp {
class ExpressionParser : Parser<ast::ExprNode> {
 public:
  // TODO(Gab): Decide on how to implement expression parser. Use CYK or some other grammar algorithm?
  // Alternative would be to bruteforce all possible trees and memoise.
  std::unique_ptr<ast::ExprNode> parse(Lexer& lxr);
};
}  // namespace sp
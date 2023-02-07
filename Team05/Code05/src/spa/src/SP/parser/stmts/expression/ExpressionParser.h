#pragma once

#include "SP/parser/Parser.h"
#include "models/AST/factor_node/FactorNode.h"

namespace sp {
class ExpressionParser : Parser<ast::ExprNode> {
 public:
  std::unique_ptr<ast::ExprNode> parse(Lexer&) {
    // todo(Gab): Bring code for expression here
    return nullptr;
  }

};
}  // namespace sp
#pragma once

#include <memory>

#include "SP/lexer/VectorLexer.h"
#include "SP/parser/Parser.h"
#include "models/AST/factor_node/FactorNode.h"

namespace sp {
class ExpressionParser : Parser<ast::ExprNode> {
 public:
  std::unique_ptr<ast::ExprNode> parse(Lexer& lxr) override;
  ast::ExprNodePtr parse(VectorLexer& lxr);
};
}  // namespace sp

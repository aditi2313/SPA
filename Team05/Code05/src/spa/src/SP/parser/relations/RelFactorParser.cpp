#include "RelFactorParser.h"

#include "SP/parser/expression/ExpressionParser.h"

namespace sp {
std::unique_ptr<ast::RelFactor> RelFactorParser::parse(Lexer& lxr) {
  auto expr = expr_parser_.parse(lxr);
  auto result = std::make_unique<ast::RelFactor>(std::move(expr));
  return std::move(result);
}

}  // namespace sp

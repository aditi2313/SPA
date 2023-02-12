#pragma once

#include <memory>

#include "SP/parser/Parser.h"
#include "SP/parser/expression/ExpressionParser.h"
#include "models/AST/relations/RelExprNode.h"

namespace sp {
class RelFactorParser : public SelectClParser<ast::RelFactor> {
 public:
  std::unique_ptr<ast::RelFactor> parse(Lexer&) override;

 private:
  ExpressionParser expr_parser_;
};

}  // namespace sp

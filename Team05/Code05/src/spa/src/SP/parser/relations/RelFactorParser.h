#pragma once

#include <memory>

#include "SP/parser/Parser.h"
#include "models/AST/relations/RelExprNode.h"
#include "SP/parser/expression/ExpressionParser.h"

namespace sp {
class RelFactorParser : public Parser<ast::RelFactor> {
 public:
  std::unique_ptr<ast::RelFactor> parse(Lexer&) override;

 private:
  ExpressionParser expr_parser_;
};

}

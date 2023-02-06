#pragma once

#include "SP/parser/Parser.h"
#include "models/AST/factor_node/FactorNode.h"

namespace sp {
class TimesParser : Parser<ast::TimesNode> {
 public:
  std::unique_ptr<ast::TimesNode> parse(Lexer&) {}
};
}  // namespace sp
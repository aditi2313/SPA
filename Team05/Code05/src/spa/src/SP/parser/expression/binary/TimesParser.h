#pragma once

#include <memory>

#include "SP/parser/Parser.h"
#include "models/AST/factor_node/FactorNode.h"

namespace sp {
class TimesParser : SelectClParser<ast::TimesNode> {
 public:
  std::unique_ptr<ast::TimesNode> parse(Lexer&) { return nullptr; }
};
}  // namespace sp

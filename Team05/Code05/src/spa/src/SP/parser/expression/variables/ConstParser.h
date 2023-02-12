#pragma once

#include <memory>

#include "SP/parser/Parser.h"
#include "models/AST/factor_node/FactorNode.h"

namespace sp {
class ConstParser : SelectClParser<ast::ConstNode> {
 public:
  std::unique_ptr<ast::ConstNode> parse(Lexer&) { return nullptr; }
};
}  // namespace sp

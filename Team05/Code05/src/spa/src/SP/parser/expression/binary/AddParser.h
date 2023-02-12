#pragma once

#include <memory>

#include "SP/parser/Parser.h"
#include "models/AST/factor_node/FactorNode.h"

namespace sp {
class AddParser : SelectClParser<ast::PlusNode> {
 public:
  std::unique_ptr<ast::PlusNode> parse(Lexer&) { return nullptr; }
};
}  // namespace sp

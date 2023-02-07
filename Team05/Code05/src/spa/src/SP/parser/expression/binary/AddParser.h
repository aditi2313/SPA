#pragma once

#include "SP/parser/Parser.h"
#include "models/AST/factor_node/FactorNode.h"

namespace sp {
class AddParser : Parser<ast::PlusNode> {
 public:
  std::unique_ptr<ast::PlusNode> parse(Lexer&) { return nullptr;
  }

};
}  // namespace sp

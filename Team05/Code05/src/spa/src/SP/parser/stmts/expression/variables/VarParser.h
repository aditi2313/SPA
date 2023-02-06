#pragma once

#include "SP/parser/Parser.h"
#include "models/AST/factor_node/FactorNode.h"

namespace sp {
class AddParser : Parser<ast::VarNode> {
 public:
  std::unique_ptr<ast::VarNode> parse(Lexer&) {}
};
}  // namespace sp
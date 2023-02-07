#pragma once

#include <memory>

#include "SP/parser/Parser.h"
#include "models/AST/factor_node/FactorNode.h"

namespace sp {
class AddParser : Parser<ast::MinusNode> {
 public:
  std::unique_ptr<ast::MinusNode> parse(Lexer&) { return nullptr; }
};
}  // namespace sp

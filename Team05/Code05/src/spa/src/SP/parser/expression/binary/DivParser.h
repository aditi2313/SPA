#pragma once

#include <memory>

#include "SP/parser/Parser.h"
#include "models/AST/factor_node/FactorNode.h"

namespace sp {
class DivParser : Parser<ast::DivNode> {
 public:
  std::unique_ptr<ast::DivNode> parse(Lexer&) { return nullptr; }
};
}  // namespace sp
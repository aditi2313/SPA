#pragma once

#include <memory>
#include "models/AST/factor_node/FactorNode.h"
#include "SP/parser/Parser.h"

namespace sp {

class TermParser : Parser<ast::TermNode> {
 public:
  std::unique_ptr<ast::TermNode> parse(Lexer& lxr) override;
};

}  // namespace sp

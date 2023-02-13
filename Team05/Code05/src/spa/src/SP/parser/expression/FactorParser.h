#pragma once

#include <memory>
#include "SP/parser/Parser.h"
#include "models/AST/factor_node/FactorNode.h"

namespace sp {

class FactorParser : public Parser<ast::FactorNode>{
 public:
  std::unique_ptr<ast::FactorNode> parse(Lexer& lxr) override;
};

}  // namespace sp

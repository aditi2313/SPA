#pragma once

#include <memory>
#include "../../../models/AST/factor_node/FactorNode.h"
#include "../Parser.h"

namespace sp {

class FactorParser : public Parser<ast::FactorNode>{
 public:
  std::unique_ptr<ast::FactorNode> parse(Lexer& lxr) override;
};

}  // namespace sp

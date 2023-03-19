#pragma once

#include <memory>

#include "SP/lexer/VectorLexer.h"
#include "SP/parser/Parser.h"
#include "models/AST/factor_node/FactorNode.h"

namespace sp {

class FactorParser {
 public:
  ast::ExprNodePtr parse(VectorLexer& lxr);
};

}  // namespace sp

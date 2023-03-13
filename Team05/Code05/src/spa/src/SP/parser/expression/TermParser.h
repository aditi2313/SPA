#pragma once

#include <memory>

#include "SP/lexer/VectorLexer.h"
#include "SP/parser/Parser.h"
#include "models/AST/factor_node/FactorNode.h"
#include "models/AST/factor_node/StringExpr.h"

namespace sp {

class TermParser {
 public:
  ast::ExprNodePtr parse(VectorLexer& lxr);
  void ParseStringExpr(VectorLexer& lxr, ast::StringExpr&);
};

}  // namespace sp

#pragma once

#include <memory>

#include "SP/parser/Parser.h"
#include "models/AST/relations/CondExprNode.h"

namespace sp {
class CondExprParser : public SelectClParser<ast::CondExprNode> {
 public:
  std::unique_ptr<ast::CondExprNode> parse(Lexer&) override;
};
}  // namespace sp

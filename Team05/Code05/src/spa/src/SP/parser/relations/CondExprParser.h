#pragma once

#include <memory>

#include "SP/parser/Parser.h"
#include "models/AST/Export.h"

namespace sp {
class CondExprParser : public Parser<ast::CondExprNode> {
 public:
  std::unique_ptr<ast::CondExprNode> parse(Lexer&) override;
};
}  // namespace sp

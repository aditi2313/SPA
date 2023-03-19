#pragma once

#include <memory>
#include <utility>

#include "SP/parser/Parser.h"
#include "models/AST/relations/Export.h"
#include "SP/parser/relations/RelFactorParser.h"

namespace sp {
class RelExprParser : public Parser<ast::RelExprNode> {
 public:
  std::unique_ptr<ast::RelExprNode> parse(Lexer&) override;

 private:
  RelFactorParser rel_parser_;
};
}  // namespace sp

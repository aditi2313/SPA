#pragma once

#include <memory>
#include <utility>

#include "SP/parser/Parser.h"
#include "models/AST/Export.h"

namespace sp {
class StatementParser : Parser<ast::StmtNode> {
 public:
  std::unique_ptr<ast::StmtNode> parse(Lexer&) override;
};
}  // namespace sp

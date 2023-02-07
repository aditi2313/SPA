#pragma once

#include "SP/parser/Parser.h"
#include "models/AST/stmt_node/StmtNode.h"

namespace sp {
class StatementParser : Parser<ast::StmtNode> {
 public:
  std::unique_ptr<ast::StmtNode> parse(Lexer&);
};
}  // namespace sp
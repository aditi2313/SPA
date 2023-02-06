#pragma once

#include "SP/parser/Parser.h"
#include "models/AST/stmt_node/StmtNode.h"

namespace sp {
class StatementParser : Parser<ast::StmtNode> {
 public:
  StatementParser(ProgramParser* parent, int prev_token) : prev_token_(prev_token) { parent_ = parent; }

  std::unique_ptr<ast::StmtNode> parse(Lexer&);

 private:
  ProgramParser* parent_;
  int prev_token_;
};
}  // namespace sp
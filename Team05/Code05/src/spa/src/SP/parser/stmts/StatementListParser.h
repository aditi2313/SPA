#pragma once

#include "SP/parser/Parser.h"
#include "SP/parser/ProgramParser.h"
#include "models/AST/StmtLstNode.h"

namespace sp {
class StatementListParser : Parser<ast::StmtLstNode> {
 public:
  StatementListParser(ProgramParser* parent) { parent_ = parent; }

  std::unique_ptr<ast::StmtLstNode> parse(Lexer&);

 private:
  ProgramParser* parent_;
};
}  // namespace sp

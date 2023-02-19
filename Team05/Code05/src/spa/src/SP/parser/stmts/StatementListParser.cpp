#include "StatementListParser.h"

#include <stdexcept>

#include "StatementParser.h"
#include "common/exceptions/SP.h"
#include "models/AST/Token.h"

namespace sp {

std::unique_ptr<ast::StmtLstNode> StatementListParser::parse(Lexer& lxr) {
  Token current_tok = lxr.get_tok();
  std::vector<std::unique_ptr<ast::StmtNode>> stmt_nodes;
  while (IsKeyWordToken(current_tok)) {
    StatementParser stmt_parser;
    stmt_nodes.push_back(std::move(stmt_parser.parse(lxr)));
    current_tok = lxr.get_tok();
  }

  if (stmt_nodes.empty()) {
    throw ParseStmtLstSyntaxException("expected at least 1 statement");
  }

  return std::make_unique<ast::StmtLstNode>(
      ast::StmtLstNode(std::move(stmt_nodes)));
}

}  // namespace sp

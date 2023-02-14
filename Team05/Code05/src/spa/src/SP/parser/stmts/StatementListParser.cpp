#include "StatementListParser.h"

#include <stdexcept>

#include "StatementParser.h"

namespace sp {
bool IsStmt(Token tok) {
  // TODO(Gab) Check if kTokProcedure should be removed from this
  // + implement this functionality inside of Token class if we are going to
  // create one #40
  return tok == Token::kTokProcedure || tok == Token::kTokRead ||
         tok == Token::kTokPrint || tok == Token::kTokCall ||
         tok == Token::kTokWhile || tok == Token::kTokIf ||
         tok == Token::kTokIdent;
}

std::unique_ptr<ast::StmtLstNode> StatementListParser::parse(Lexer& lxr) {
  Token current_tok = lxr.get_tok();

  std::vector<std::unique_ptr<ast::StmtNode>> stmt_nodes;
  while (IsStmt(current_tok)) {
    StatementParser stmt_parser;
    stmt_nodes.push_back(std::move(stmt_parser.parse(lxr)));
    current_tok = lxr.get_tok();
  }

  if (stmt_nodes.empty()) {
    throw std::runtime_error("expected at least 1 stmt in stmtLst");
  }

  auto stmt_lst_node = std::make_unique<ast::StmtLstNode>(
      ast::StmtLstNode(std::move(stmt_nodes)));
  return stmt_lst_node;
}

}  // namespace sp

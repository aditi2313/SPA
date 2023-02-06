#include "StatementListParser.h"

#include "StatementParser.h"

namespace sp {
bool IsStmt(int tok) {
  // TODO(Gab) Check if kTokProcedure should be removed from this
  return current_tok == kTokProcedure || current_tok == kTokRead ||
         current_tok == kTokPrint || current_tok == kTokCall ||
         current_tok == kTokWhile || current_tok == kTokIf ||
         current_tok == kTokIdent;
}

std::unique_ptr<ast::StmtLstNode> StatementListParser::parse(Lexer& lxr) {
  int current_tok = lxr.GetTok();

  std::vector<std::unique_ptr<ast::StmtNode>> stmt_nodes;
  while (IsStmt(current_tok)) {
    StatementParser stmt_parser(this->parent_, current_tok);
    stmt_nodes.push_back(std::move(stmt_parser.parse(lxr)));
    current_tok = lxr.GetTok();
  }

  if (stmt_nodes.empty()) {
    throw std::runtime_error("expected at least 1 stmt in stmtLst");
  }

  auto stmt_lst_node = std::make_unique<ast::StmtLstNode>(
      ast::StmtLstNode(std::move(stmt_nodes)));
  return stmt_lst_node;
}

}  // namespace sp

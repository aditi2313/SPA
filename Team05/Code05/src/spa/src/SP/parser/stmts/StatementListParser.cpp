#include "StatementListParser.h"

#include <stdexcept>

#include "StatementParser.h"
#include "models/AST/Token.h"

namespace sp {

std::unique_ptr<ast::StmtLstNode> StatementListParser::parse(Lexer& lxr) {
  Token current_tok = lxr.get_tok();

  std::vector<std::unique_ptr<ast::StmtNode>> stmt_nodes;
  while (IsStmtToken(current_tok)) {
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

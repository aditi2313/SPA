#include "ProcedureParser.h"

#include <iostream>
#include <utility>
#include <string>

#include "stmts/StatementListParser.h"
#include "models/AST/Token.h"

namespace sp {
std::unique_ptr<ast::ProcNode> ProcedureParser::parse(Lexer& lxr) {
  StatementListParser stmt_list_parser;
  if (!IsKeyWordToken(lxr.get_tok())) {
    // TODO(aizatazhar): use custom exception
    throw std::runtime_error("procedure should be followed by a name");
  }

  std::string proc_name = lxr.get_ident();
  lxr.Increment();
  std::cout << "procedure" << std::endl;

  if (lxr.GetTokAndIncrement() != Token::kTokOpenCurly) {
    // TODO(aizatazhar): use custom exception
    throw std::runtime_error("expected '{' after procedure name");
  }

  std::unique_ptr<ast::ProcNode> proc_node =
      std::make_unique<ast::ProcNode>(proc_name, stmt_list_parser.parse(lxr));

  if (lxr.GetTokAndIncrement() != Token::kTokCloseCurly) {
    // TODO(aizatazhar): use custom exception
    throw std::runtime_error("expected '}' after procedure stmtLst");
  }

  return std::move(proc_node);
}

}  // namespace sp

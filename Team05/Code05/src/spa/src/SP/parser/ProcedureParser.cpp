#include "ProcedureParser.h"

#include <iostream>

#include "ProgramParser.h"
#include "stmts/StatementListParser.h"

namespace sp {
std::unique_ptr<ast::ProcNode> ProcedureParser::parse(Lexer& lxr) {
  StatementListParser stmt_list_parser;
  if (lxr.GetTok() != kTokIdent) {
    // TODO(aizatazhar): use custom exception
    throw std::runtime_error("procedure should be followed by a name");
  }

  std::string proc_name = lxr.get_ident();
  lxr.Increment();
  std::cout << "procedure" << std::endl;

  if (lxr.GetTokAndIncrement() != kTokOpenCurly) {
    // TODO(aizatazhar): use custom exception
    throw std::runtime_error("expected '{' after procedure name");
  }

  std::unique_ptr<ast::ProcNode> proc_node =
      std::make_unique<ast::ProcNode>(proc_name, stmt_list_parser.parse(lxr));

  if (lxr.GetTokAndIncrement() != kTokCloseCurly) {
    // TODO(aizatazhar): use custom exception
    throw std::runtime_error("expected '}' after procedure stmtLst");
  }

  return std::move(proc_node);
}

}  // namespace sp
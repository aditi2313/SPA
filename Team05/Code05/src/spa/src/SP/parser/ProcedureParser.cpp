#include "ProcedureParser.h"

#include <string>
#include <utility>

#include "common/exceptions/SPExceptions.h"
#include "models/AST/Token.h"
#include "stmts/StatementListParser.h"

namespace sp {
std::unique_ptr<ast::ProcNode> ProcedureParser::parse(Lexer& lxr) {
  AssertExpectedToken(
      ParseProcedureSyntaxException::kParseProcedureSyntaxMessage,
      lxr.GetTokAndIncrement(), Token::kTokProcedure);
  if (!IsKeyWordToken(lxr.get_tok())) {
    throw ParseProcedureSyntaxException("expected procedure name");
  }

  std::string proc_name = lxr.get_ident();
  lxr.set_current_procedure(proc_name);
  lxr.Increment();

  AssertExpectedToken(
      ParseProcedureSyntaxException::kParseProcedureSyntaxMessage,
      lxr.GetTokAndIncrement(), Token::kTokOpenCurly);

  StatementListParser stmt_list_parser;
  std::unique_ptr<ast::ProcNode> proc_node =
      std::make_unique<ast::ProcNode>(proc_name, stmt_list_parser.parse(lxr));

  AssertExpectedToken(
      ParseProcedureSyntaxException::kParseProcedureSyntaxMessage,
      lxr.GetTokAndIncrement(), Token::kTokCloseCurly);

  return std::move(proc_node);
}

}  // namespace sp

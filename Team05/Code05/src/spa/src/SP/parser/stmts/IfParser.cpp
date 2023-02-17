#include "IfParser.h"

namespace sp {

std::unique_ptr<ast::StmtLstNode> ParseCodeBlock(Lexer& lxr) {
  AssertExpectedToken(lxr.GetTokAndIncrement(), Token::kTokOpenCurly, "{");
  StatementListParser stmt_list_parser;
  auto result = stmt_list_parser.parse(lxr);
  AssertExpectedToken(lxr.GetTokAndIncrement(), Token::kTokCloseCurly, "}");
  return std::move(result);
}

std::unique_ptr<ast::IfNode> IfParser::parse(Lexer& lxr) {
  CondExprParser cond_parser;

  AssertExpectedToken(lxr.GetTokAndIncrement(), Token::kTokIf, "if");

  AssertExpectedToken(lxr.GetTokAndIncrement(), Token::kTokOpenBracket, "(");

  auto cond_expr = cond_parser.parse(lxr);

  AssertExpectedToken(lxr.GetTokAndIncrement(), Token::kTokCloseBracket, ")");

  AssertExpectedToken(lxr.GetTokAndIncrement(), Token::kTokThen, "then");

  auto list_1 = ParseCodeBlock(lxr);

  AssertExpectedToken(lxr.GetTokAndIncrement(), Token::kTokElse, "else");

  auto list_2 = ParseCodeBlock(lxr);

  return std::make_unique<ast::IfNode>(std::move(cond_expr), std::move(list_1),
                                       std::move(list_2),
                                       lxr.GetAndIncrementStmtCtr());
}
}  // namespace sp

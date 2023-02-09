#include "CondExprParser.h"

#include <utility>

#include "RelExprParser.h"
#include "common/exceptions/SP.h"

namespace sp {
void AssertOpenBracket(Lexer& lxr) {
  if (lxr.GetTokAndIncrement() == Token::kTokOpenBracket) return;
  throw ParseRelationSyntaxException();
}

void AssertCloseBracket(Lexer& lxr) {
  if (lxr.GetTokAndIncrement() == Token::kTokCloseBracket) return;
  throw ParseRelationSyntaxException();
}
std::unique_ptr<ast::CondExprNode> ParseDoubleCond(Lexer& lxr) {
  AssertOpenBracket(lxr);
  CondExprParser cond_expr_parser;
  auto left = cond_expr_parser.parse(lxr);
  AssertCloseBracket(lxr);

  auto mid = lxr.get_tok();
  lxr.Increment();

  AssertOpenBracket(lxr);
  auto right = cond_expr_parser.parse(lxr);
  AssertCloseBracket(lxr);

  if (mid == kTokAnd) {
    return std::make_unique<ast::AndExprNode>(std::move(left),
                                              std::move(right));
  }
  if (mid == kTokOr) {
    return std::make_unique<ast::OrExprNode>(std::move(left), std::move(right));
  }
  throw ParseRelationSyntaxException();
}

std::unique_ptr<ast::CondExprNode> ParseNot(Lexer& lxr) {
  lxr.Increment();
  // pop the brackets
  AssertOpenBracket(lxr);
  CondExprParser cond_expr_parser;
  auto inner_cond = cond_expr_parser.parse(lxr);

  AssertCloseBracket(lxr);

  return std::make_unique<ast::NotExprNode>(std::move(inner_cond));
}

std::unique_ptr<ast::CondExprNode> CondExprParser::parse(Lexer& lxr) {
  // deal with case with not
  if (lxr.get_tok() == Token::kTokNot) {
    return ParseNot(lxr);
  }

  // deal with case with bracket
  if (lxr.get_tok() == Token::kTokOpenBracket) {
    return ParseDoubleCond(lxr);
  }
  RelExprParser rel_expr_parser;
  // deal with case without bracket
  return rel_expr_parser.parse(lxr);
}
}  // namespace sp

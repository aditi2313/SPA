#include "FactorParser.h"

#include "ExpressionParser.h"
#include "common/exceptions/SP.h"

namespace sp {
ast::ExprNodePtr FactorParser::parse(VectorLexer &lxr) {
  if (IsKeyWordToken(lxr.get_tok())) {
    auto res = std::make_unique<ast::VarNode>(lxr.get_ident());
    lxr.Decrement();
    return std::move(res);
  }

  if (lxr.get_tok() == Token::kTokInteger) {
    auto res = std::make_unique<ast::ConstNode>(lxr.get_integer());
    lxr.Decrement();
    return std::move(res);
  }

  if (lxr.get_tok() == Token::kTokCloseBracket) {
    lxr.Decrement();
    ExpressionParser expr_parser;
    auto res = expr_parser.parse(lxr);
    AssertExpectedToken(lxr.get_tok(), Token::kTokOpenBracket, "(");
    lxr.Decrement();
    return std::move(res);
  }

  throw LexerException("Expected a factor node");
}
}  // namespace sp
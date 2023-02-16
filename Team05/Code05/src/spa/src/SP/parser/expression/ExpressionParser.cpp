#include "ExpressionParser.h"

#include <memory>
#include <stdexcept>
#include <utility>

#include "TermParser.h"

namespace sp {

ast::ExprNodePtr ExpressionParser::parse(Lexer& lxr) {
  VectorLexer v_lexer(lxr);
  return parse(v_lexer);
}

ast::ExprNodePtr ExpressionParser::parse(VectorLexer& lxr) {
  TermParser term_parser;
  auto term = term_parser.parse(lxr);
  if (lxr.get_tok() == Token::kTokPlus || lxr.get_tok() == Token::kTokMinus) {
    auto op = lxr.get_tok();
    lxr.Decrement();
    auto res = parse(lxr);
    return std::make_unique<ast::OpNode>(op, std::move(term), std::move(res));
  }
  return std::move(term);
}
}  // namespace sp

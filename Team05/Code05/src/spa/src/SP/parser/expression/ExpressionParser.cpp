#include "ExpressionParser.h"

#include <memory>
#include <stdexcept>
#include <utility>

#include "TermParser.h"
#include "common/exceptions/SP.h"

namespace sp {

ast::ExprNodePtr ExpressionParser::parse(Lexer& lxr) {
  VectorLexer v_lexer(lxr);
  auto result = parse(v_lexer);
  if (v_lexer.get_tok() != Token::kTokEof) {
    throw ParseException("Extra token at the front of expression");
  }
  return std::move(result);
}

ast::ExprNodePtr ExpressionParser::parse(VectorLexer& lxr) {
  TermParser term_parser;
  auto term = term_parser.parse(lxr);
  if (lxr.get_tok() == Token::kTokPlus || lxr.get_tok() == Token::kTokMinus) {
    auto op = lxr.get_tok();
    lxr.Decrement();
    auto res = parse(lxr);
    return std::make_unique<ast::OpNode>(op, std::move(res), std::move(term));
  }
  return std::move(term);
}
}  // namespace sp

#include "ExpressionParser.h"

#include <memory>
#include <stdexcept>
#include <utility>

#include "common/exceptions/SP.h"
#include "TermParser.h"

namespace sp {

ast::ExprNodePtr ExpressionParser::parse(Lexer& lxr) {
  VectorLexer v_lexer(lxr);
  // if the start of the vector lexer has a bracket
  // the end should have one as well
  bool end_bracket = v_lexer.get_tok() == Token::kTokCloseBracket;
  auto result = parse(v_lexer);
  if (v_lexer.get_tok() == Token::kTokOpenBracket && !end_bracket) {
    throw ParseException("Missing bracket at end of expression");
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

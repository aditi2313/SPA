#include "TermParser.h"

#include <stdexcept>
#include <utility>

#include "FactorParser.h"

namespace sp {
ast::ExprNodePtr TermParser::parse(VectorLexer& lxr) {
  FactorParser factor_parser;
  auto factor = factor_parser.parse(lxr);
  if (lxr.get_tok() == Token::kTokTimes || lxr.get_tok() == Token::kTokDiv ||
      lxr.get_tok() == Token::kTokMod) {
    auto op = lxr.get_tok();
    lxr.Decrement();
    auto term = parse(lxr);
    return std::make_unique<ast::OpNode>(op, std::move(term),
                                         std::move(factor));
  }
  return std::move(factor);
}

void TermParser::ParseStringExpr(VectorLexer& lxr, ast::StringExpr& expr) {
  auto c_pt = expr.insert_empty();
  FactorParser factor_parser;
  factor_parser.ParseStringExpr(lxr, expr);
  if (lxr.get_tok() == Token::kTokTimes || lxr.get_tok() == Token::kTokDiv ||
      lxr.get_tok() == Token::kTokMod) {
    expr.add_close(c_pt);
    auto op = lxr.get_tok();
    lxr.Decrement();
    expr.add_token(op);
    ParseStringExpr(lxr, expr);
    expr.add_open();
  }
}

}  // namespace sp

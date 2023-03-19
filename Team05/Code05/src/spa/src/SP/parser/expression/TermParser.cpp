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

}  // namespace sp

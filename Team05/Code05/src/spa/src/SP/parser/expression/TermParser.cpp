#include <utility>
#include "TermParser.h"
#include "FactorParser.h"

namespace sp {
std::unique_ptr<ast::TermNode> TermParser::parse(Lexer &lxr) {
  sp::FactorParser factor_parser;

  // Reached end of statement - don't eat the current token
  // so that FactorParser can parse correctly
  if (lxr.Peek() == Token::kTokSemicolon) {
    return factor_parser.parse(lxr);
  }

  auto lhs = std::make_unique<ast::VarNode>(ast::VarNode(lxr.get_ident()));
  lxr.Increment();  // eat ident
  auto op = lxr.GetTokAndIncrement();
  auto rhs = factor_parser.parse(lxr);

  if (op == kTokTimes) {
    return std::make_unique<ast::TimesNode>(
        ast::TimesNode(std::move(lhs), std::move(rhs)));
  } else if (op == kTokDiv) {
    return std::make_unique<ast::DivNode>(
        ast::DivNode(std::move(lhs), std::move(rhs)));
  } else if (op == kTokMod) {
    return std::make_unique<ast::ModNode>(
        ast::ModNode(std::move(lhs), std::move(rhs)));
  }

  throw std::runtime_error("TermParser unknown token");
}
}  // namespace sp

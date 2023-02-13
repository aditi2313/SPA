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

  auto lhs_ident = lxr.get_ident();
  lxr.Increment();  // eat ident
  auto op = lxr.GetTokAndIncrement();

  if (op == kTokTimes) {
    auto lhs = std::make_unique<ast::VarNode>(ast::VarNode(lhs_ident));
    auto rhs = factor_parser.parse(lxr);
    return std::make_unique<ast::TimesNode>(
        ast::TimesNode(std::move(lhs), std::move(rhs)));
  } else if (op == kTokDiv) {
    auto lhs = std::make_unique<ast::VarNode>(ast::VarNode(lhs_ident));
    auto rhs = factor_parser.parse(lxr);
    return std::make_unique<ast::DivNode>(
        ast::DivNode(std::move(lhs), std::move(rhs)));
  } else if (op == kTokMod) {
    auto lhs = std::make_unique<ast::VarNode>(ast::VarNode(lhs_ident));
    auto rhs = factor_parser.parse(lxr);
    return std::make_unique<ast::ModNode>(
        ast::ModNode(std::move(lhs), std::move(rhs)));
  }

  throw std::runtime_error("TermParser unknown token");
}
}  // namespace sp

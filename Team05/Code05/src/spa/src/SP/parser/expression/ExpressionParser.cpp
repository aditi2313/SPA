#include "ExpressionParser.h"

#include <memory>
#include <utility>

namespace sp {

std::unique_ptr<ast::ExprNode> ExpressionParser::parse(Lexer& lxr) {
  // todo(Gab): Bring code for expression here
  if (lxr.GetTokAndIncrement() != kTokIdent) {
    // TODO(aizatazhar): use custom exception
    throw std::runtime_error("expected an expression");
  }

  auto lhs = std::make_unique<ast::VarNode>(ast::VarNode(lxr.get_ident()));

  int op = lxr.GetTokAndIncrement();
  auto rhs = std::make_unique<ast::VarNode>(ast::VarNode(lxr.get_ident()));

  lxr.Increment();
  if (op == kTokPlus) {
    return std::make_unique<ast::PlusNode>(
        ast::PlusNode(std::move(lhs), std::move(rhs)));
  } else if (op == kTokMinus) {
    return std::make_unique<ast::MinusNode>(
        ast::MinusNode(std::move(lhs), std::move(rhs)));
  } else {
    // TODO(aizatazhar): use custom exception
    throw std::runtime_error("unknown token");
  }
}
}  // namespace sp

#pragma once

#include "SP/parser/Parser.h"
#include "models/AST/factor_node/FactorNode.h"

namespace sp {
class ExpressionParser : Parser<ast::ExprNode> {
 public:
  std::unique_ptr<ast::ExprNode> parse(Lexer& lxr) {
    // todo(Gab): Bring code for expression here
    if (lxr.GetTokAndIncrement() != kTokIdent) {
      // TODO(aizatazhar): use custom exception
      throw std::runtime_error("expected an expression");
    }

    auto lhs =
        std::make_unique<ast::VarNode>(ast::VarNode(lxr.get_ident()));

    int op = lxr.GetTokAndIncrement();

    lxr.Increment();

    auto rhs =
        std::make_unique<ast::VarNode>(ast::VarNode(lxr.get_ident()));

    if (op == kTokPlus) {
      lxr.GetTokAndIncrement();
      return std::make_unique<ast::PlusNode>(
          ast::PlusNode(std::move(rhs), std::move(lhs)));
    } else if (op == kTokMinus) {
      lxr.GetTokAndIncrement();
      return std::make_unique<ast::MinusNode>(
          ast::MinusNode(std::move(rhs), std::move(lhs)));
    } else {
      // TODO(aizatazhar): use custom exception
      throw std::runtime_error("unknown token");
    }
  }
};
}  // namespace sp
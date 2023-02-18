#pragma once

#include <memory>
#include <stdexcept>
#include <utility>

#include "SP/parser/Parser.h"
#include "SP/parser/ProgramParser.h"
#include "SP/parser/expression/ExpressionParser.h"
#include "common/exceptions/SP.h"
#include "models/AST/stmt_node/StmtNode.h"

namespace sp {
class AssignParser : Parser<ast::AssignNode> {
 public:
  std::unique_ptr<ast::AssignNode> parse(Lexer& lxr) {
    lxr.Increment(); // eat the lhs variable

    auto var_node =
        std::make_unique<ast::VarNode>(ast::VarNode(lxr.get_ident()));
    ExpressionParser expr_parser;

    AssertExpectedToken(lxr.GetTokAndIncrement(), Token::kTokEquals, "=");

    auto expr = expr_parser.parse(lxr);
    if (lxr.GetTokAndIncrement() != Token::kTokSemicolon) {
      throw ParseAssignSyntaxException();
    }

    return std::make_unique<ast::AssignNode>(
        std::move(var_node), std::move(expr), lxr.GetAndIncrementStmtCtr());
  }
};
}  // namespace sp

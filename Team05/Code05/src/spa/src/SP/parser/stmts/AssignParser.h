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
  std::unique_ptr<ast::AssignNode> parse(Lexer& lxr) override {
    if (!IsKeyWordToken(lxr.get_tok())) {
      throw ParseAssignSyntaxException("expected a variable name");
    }

    auto ident = lxr.get_ident();
    lxr.Increment();
    auto var_node =
        std::make_unique<ast::VarNode>(ast::VarNode(ident));

    AssertExpectedToken(ParseAssignSyntaxException::kParseAssignSyntaxMessage,
                        lxr.GetTokAndIncrement(), Token::kTokEquals);

    ExpressionParser expr_parser;
    auto expr = expr_parser.parse(lxr);

    AssertExpectedToken(ParseAssignSyntaxException::kParseAssignSyntaxMessage,
                        lxr.GetTokAndIncrement(), Token::kTokSemicolon);

    return std::make_unique<ast::AssignNode>(
        std::move(var_node), std::move(expr), lxr.GetAndIncrementStmtCtr());
  }
};
}  // namespace sp

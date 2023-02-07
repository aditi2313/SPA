#pragma once

#include "SP/parser/Parser.h"
#include "SP/parser/ProgramParser.h"
#include "SP/parser/expression/ExpressionParser.h"
#include "models/AST/stmt_node/StmtNode.h"

namespace sp {
class AssignParser : Parser<ast::AssignNode> {
 public:
  std::unique_ptr<ast::AssignNode> parse(Lexer& lxr) {
    auto var_node =
        std::make_unique<ast::VarNode>(ast::VarNode(lxr.get_ident()));
    ExpressionParser expr_parser;
    if (lxr.GetTokAndIncrement() != kTokEquals) {
      // TODO(aizatazhar): use custom exception
      throw std::runtime_error("expected '=' in assignment");
    }

    return std::make_unique<ast::AssignNode>(std::move(var_node),
                                             expr_parser.parse(lxr),
                                             lxr.GetAndIncrementStmtCtr());
  }
};
}  // namespace sp
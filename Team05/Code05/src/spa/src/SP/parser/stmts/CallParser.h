#pragma once
#include <iostream>
#include <memory>
#include <utility>
#include <string>

#include "SP/parser/Parser.h"
#include "SP/parser/ProgramParser.h"
#include "models/AST/factor_node/FactorNode.h"
#include "models/AST/stmt_node/StmtNode.h"

namespace sp {
class CallParser : Parser<ast::CallNode> {
 public:
  std::unique_ptr<ast::CallNode> parse(Lexer& lxr) override {
    AssertExpectedToken(lxr.GetTokAndIncrement(), Token::kTokCall, "call");
    AssertExpectedToken(lxr.GetTokAndIncrement(), Token::kTokIdent, "variable");

    std::string var_name = lxr.get_ident();
    std::cout << "call " + lxr.get_ident() << std::endl;

    AssertExpectedToken(lxr.GetTokAndIncrement(), Token::kTokSemicolon, ";");

    auto var_node = std::make_unique<ast::VarNode>(ast::VarNode(var_name));
    return std::make_unique<ast::CallNode>(std::move(var_node),
                                           lxr.GetAndIncrementStmtCtr());
  }
};
}  // namespace sp

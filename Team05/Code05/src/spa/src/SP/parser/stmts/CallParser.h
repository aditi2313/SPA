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
    AssertExpectedToken(ParseCallSyntaxException::kParseCallSyntaxMessage,
                        lxr.GetTokAndIncrement(), Token::kTokCall);

    if (!IsKeyWordToken(lxr.GetTokAndIncrement())) {
      throw ParseCallSyntaxException("call should be followed by a name");
    }

    std::string var_name = lxr.get_ident();

    AssertExpectedToken(ParseCallSyntaxException::kParseCallSyntaxMessage,
                        lxr.GetTokAndIncrement(), Token::kTokSemicolon);

    auto var_node = std::make_unique<ast::VarNode>(ast::VarNode(var_name));
    return std::make_unique<ast::CallNode>(std::move(var_node),
                                           lxr.GetAndIncrementStmtCtr());
  }
};
}  // namespace sp

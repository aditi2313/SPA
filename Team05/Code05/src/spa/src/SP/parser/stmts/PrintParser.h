#pragma once

#include <memory>
#include <utility>
#include <string>

#include "SP/parser/Parser.h"
#include "models/AST/stmt_node/StmtNode.h"

namespace sp {
class PrintParser : Parser<ast::PrintNode> {
 public:
  std::unique_ptr<ast::PrintNode> parse(Lexer& lxr) override {
    AssertExpectedToken(lxr.GetTokAndIncrement(), Token::kTokPrint, "print");
    if (!IsKeyWordToken(lxr.GetTokAndIncrement())) {
      // TODO(aizatazhar): use custom exception
      throw std::runtime_error("print should be followed by a name");
    }
    std::string var_name = lxr.get_ident();
    std::cout << "print " + lxr.get_ident() << std::endl;

    AssertExpectedToken(lxr.GetTokAndIncrement(), Token::kTokSemicolon, ";");

    auto var_node = std::make_unique<ast::VarNode>(ast::VarNode(var_name));
    return std::make_unique<ast::PrintNode>(
        ast::PrintNode(std::move(var_node), lxr.GetAndIncrementStmtCtr()));
  }
};
}  // namespace sp

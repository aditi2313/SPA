#pragma once

#include <memory>
#include <utility>
#include <string>

#include "SP/parser/Parser.h"
#include "SP/parser/ProgramParser.h"
#include "models/AST/stmt_node/StmtNode.h"

namespace sp {
class ReadParser : Parser<ast::ReadNode> {
 public:
  std::unique_ptr<ast::ReadNode> parse(Lexer& lxr) override {
    AssertExpectedToken(lxr.GetTokAndIncrement(), Token::kTokRead, "read");
    AssertExpectedToken(lxr.GetTokAndIncrement(), Token::kTokIdent, "variable");

    std::string var_name = lxr.get_ident();
    std::cout << "read " + lxr.get_ident() << std::endl;

    AssertExpectedToken(lxr.GetTokAndIncrement(), Token::kTokSemicolon, ";");

    auto var_node = std::make_unique<ast::VarNode>(ast::VarNode(var_name));
    return std::make_unique<ast::ReadNode>(
        ast::ReadNode(std::move(var_node), lxr.GetAndIncrementStmtCtr()));
  }

 private:
};
}  // namespace sp

#pragma once

#include <memory>
#include <utility>
#include <string>

#include "SP/parser/Parser.h"
#include "SP/parser/ProgramParser.h"
#include "models/AST/Export.h"

namespace sp {
class ReadParser : Parser<ast::ReadNode> {
 public:
  std::unique_ptr<ast::ReadNode> parse(Lexer& lxr) override {
    AssertExpectedToken(ParseReadSyntaxException::kParseReadSyntaxMessage,
                        lxr.GetTokAndIncrement(), Token::kTokRead);

    if (!IsKeyWordToken(lxr.GetTokAndIncrement())) {
      throw ParseReadSyntaxException("read should be followed by a name");
    }

    std::string var_name = lxr.get_ident();

    AssertExpectedToken(ParseReadSyntaxException::kParseReadSyntaxMessage,
                        lxr.GetTokAndIncrement(), Token::kTokSemicolon);

    auto var_node = std::make_unique<ast::VarNode>(ast::VarNode(var_name));
    return std::make_unique<ast::ReadNode>(
        ast::ReadNode(std::move(var_node), lxr.GetAndIncrementStmtCtr()));
  }
};
}  // namespace sp

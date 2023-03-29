#pragma once
#include <iostream>
#include <memory>
#include <utility>
#include <string>

#include "SP/parser/Parser.h"
#include "SP/parser/ProgramParser.h"
#include "models/AST/Export.h"

namespace sp {
class CallParser : Parser<ast::CallNode> {
 public:
  std::unique_ptr<ast::CallNode> parse(Lexer& lxr) override {
    AssertExpectedToken(ParseCallSyntaxException::kParseCallSyntaxMessage,
                        lxr.GetTokAndIncrement(), Token::kTokCall);

    if (!IsKeyWordToken(lxr.GetTokAndIncrement())) {
      throw ParseCallSyntaxException("call should be followed by a name");
    }

    AssertExpectedToken(ParseCallSyntaxException::kParseCallSyntaxMessage,
                        lxr.GetTokAndIncrement(), Token::kTokSemicolon);

    return std::make_unique<ast::CallNode>(lxr.get_current_procedure(),
                                           lxr.get_ident(),
                                           lxr.GetAndIncrementStmtCtr());
  }
};
}  // namespace sp
